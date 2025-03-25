#include "mlx/mlx.h"
#include "map/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// linux keycode
#define W 119
#define D 100
#define S 115
#define A 97
#define ESC 65307
#define X_btn 0
#define RIGHT 65363
#define LEFT 65361

// Mac keycode
// #define W 13
// #define D 2
// #define S 1
// #define A 0
// #define ESC 53
// #define RIGHT 124
// #define LEFT 123

#define HEIGHT 1080
#define WIDTH  1920

int map_height; // map 구조체 추가시 삭제
int map_width; // map 구조체 추가시 삭제

double posX = 10, posY = 10;      // 플레이어 좌표
double dirX = -1, dirY = 0;       // 플레이어의 시선 방향
double planeX, planeY; // 카메라 평면
double moveSpeed = 0.3;           // 이동 속도
double rotSpeed = 0.1;            // 회전 속도

void *img;
char *img_data;
int bpp, size_line, endian;
void *texture[4];

t_config config;

typedef struct	s_player
{
	double poxX;
	double posY;
	double dirX;
	double dirY;
	double sight_dir;
}				t_player;

typedef struct	s_camera
{
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
}				t_camera;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
}				t_mlx;

typedef struct	s_img
{
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

t_mlx mlx;
t_player player;

// 텍스처     // 텍스처 배열
char *texture_data[4];
int tex_bpp[4], tex_size_line[4], tex_endian[4];
int texWidth = 64, texHeight = 64;
int render_frame();


void set_player_direction(char direction)
{
	int index;
	double directions[4][4] = // 할당 함수로 빼기
	{
		{0, -1, 0.66, 0},
		{0, 1, -0.66, 0},
		{1, 0, 0, 0.66},
		{-1, 0, 0, -0.66}
	};

	index = 0;
	if (direction == 'N')
		index = 0;
	else if (direction == 'S')
		index = 1;
	else if (direction == 'E')
		index = 2;
	else if (direction == 'W')
		index = 3;
	dirX = directions[index][0];
	dirY = directions[index][1];
	planeX = directions[index][2];
	planeY = directions[index][3];
}

void init_image()
{
    img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
    img_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
}

void load_textures()
{
	char *texture_files[4] = {config.texture_ea, config.texture_no, config.texture_so, config.texture_we}; //map 배열로 변경
	for (int i = 0; i < 4; i++)
	{
		texture[i] = mlx_xpm_file_to_image(mlx.mlx, texture_files[i], &texWidth, &texHeight);
		if (!texture[i])
		{
			printf("Failed to load texture %s\n", texture_files[i]);
			exit(1);
		}
		else
		{
			texture_data[i] = mlx_get_data_addr(texture[i], &tex_bpp[i], &tex_size_line[i], &tex_endian[i]);
		}
	}
}



void move_player(double moveX, double moveY)
{
    // X 이동 검사
    int	newX;
    int	currentY;
	int	newY;
    int	currentX;


	newX = (int)(posX + moveX);
	currentY = (int)posY;
    if (newX >= 0 && newX < map_width && currentY >= 0 && currentY < map_height &&
        config.map[currentY][newX] == '0')
    {
        posX += moveX;
    }
    // Y 이동 검사
	newY = (int)(posY + moveY);
	currentX = (int)posX;
    if (newY >= 0 && newY < map_height && currentX >= 0 && currentX < map_width &&
        config.map[newY][currentX] == '0')
    {
        posY += moveY;
    }
}

void rotate_player(double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = dirX;
	dirX = dirX * cos(angle) - dirY * sin(angle);
	dirY = oldDirX * sin(angle) + dirY * cos(angle);

	oldPlaneX = planeX;
	planeX = planeX * cos(angle) - planeY * sin(angle);
	planeY = oldPlaneX * sin(angle) + planeY * cos(angle);
}

int keypress(int key, void *param)
{
	if (key == W)
		move_player(dirX * moveSpeed, dirY * moveSpeed);
	if (key == S)
		move_player(-dirX * moveSpeed, -dirY * moveSpeed);
	if (key == D)
		move_player(planeX * moveSpeed, planeY * moveSpeed);
	if (key == A)
		move_player(-planeX * moveSpeed, -planeY * moveSpeed);
	if (key == LEFT)
		rotate_player(-rotSpeed);
	if (key == RIGHT)
		rotate_player(rotSpeed);
	if (key == ESC || key == X_btn)
		exit(0);
	render_frame();
	return 0;
}

int render_frame()
{
	ft_memset(img_data, 0, HEIGHT * size_line);

	// 천장 바닥
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int pixel = (y * size_line) + (x * (bpp / 8));
			if (y < HEIGHT / 2)
				*(int *)(img_data + pixel) = (config.ceiling_color[0] << 16) + (config.ceiling_color[1] << 8) + (config.ceiling_color[2]);
			else
				*(int *)(img_data + pixel) = (config.floor_color[0] << 16) + (config.floor_color[1] << 8) + (config.floor_color[2]);
		}
	}

	// 벽 렌더링
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX;
		double rayDirX;
		double rayDirY;
		int mapX;
		int mapY;
		double deltaDistX;
		double deltaDistY;

		cameraX = 2 * x / (double)WIDTH - 1;
		mapX = (int)posX;
		mapY = (int)posY;
		rayDirY = dirY + planeY * cameraX;
		rayDirX = dirX + planeX * cameraX;

		if(rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);

		if(rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);

		double sideDistX;
		double sideDistY;
		int stepX;
		int stepY;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		int hit = 0, side;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// 맵 경계 확인
			if (mapX < 0 || mapX >= map_width || mapY < 0 || mapY >= map_height)
			{
				hit = 1;
			}
			// 벽 충돌 확인
			else if (config.map[mapY][mapX] > '0')
			{
				hit = 1;
			}
		}
		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		//텍스처
		int texNum;
		if (side == 0)
		{
			if (rayDirX > 0)
				texNum = 2;
			else
				texNum = 1; // 동/서
		}
		else
		{
			if (rayDirY > 0)
				texNum = 3;
			else
				texNum = 0; // 남/북
		}
		//
		double wallX;
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX;
		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		//
		double step;
		step = 1.0 * texHeight / lineHeight;
		double texPos;
		texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			// 텍스처 픽셀
			int tex_pixel = (texY * tex_size_line[texNum]) + (texX * (tex_bpp[texNum] / 8));
			int color = *(int *)(texture_data[texNum] + tex_pixel);

			if (side == 1)
				color = (color >> 1) & 0x7F7F7F;

			int pixel = (y * size_line) + (x * (bpp / 8));
			*(int *)(img_data + pixel) = color;
		}
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, img, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		write(2, "Usage: ./cub3D <scene_file.cub>\n", 32);
		exit(1);
	}
	if (!parse_file(argv[1], &config)) {
		write(2, "Failed to parse the .cub file\n", 31);
		exit(1);
	}
	map_height = config.map_lines; // 추가 되면 삭제
	map_width = 19; // 추가 되면 삭제
    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
    init_image();
    load_textures();
	mlx_string_put(mlx.mlx, mlx.mlx_win, WIDTH / 2 - 20, HEIGHT / 2, 0xFFFFFF, "Press any Key");
    set_player_direction('W'); //파싱부 sight dir 추가되면 수정 필요함
    posX = 5.5; // pos추가되면 삭제
    posY = 5.5; // pos추가되면 삭제
    mlx_hook(mlx.mlx_win, 2, 1L << 0, keypress, NULL);
	mlx_hook(mlx.mlx_win, 17,  0 , keypress, NULL);
    mlx_loop(mlx.mlx);
    return 0;
}
