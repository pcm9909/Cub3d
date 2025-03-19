#include "mlx/mlx.h"
#include "stdio.h"
#include "stdlib.h"

#include "map/map.h"

#define W 119
#define D 100
#define S 115
#define A 97
#define ESC 65307
#define X_btn 0
#define RIGHT 65363
#define LEFT 65361


void	*mlx;
void	*mlx_win;
int x,y = 10;

int keypress(int key, void *param)
{
	printf("keycode = %d\n", key);
	if(key == ESC)
		exit(0);
	if(key == W)
	{
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00FF0000);
		y--;
		printf("x = %d, y = %d\n", x, y);
	}
	if(key == D)
	{
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00FF0000);
		x++;
		printf("x = %d, y = %d\n", x, y);
	}
	if(key == A)
	{
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00FF0000);
		x--;
		printf("x = %d, y = %d\n", x, y);
	}
	if(key == S)
	{
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00FF0000);
		y++;
		printf("x = %d, y = %d\n", x, y);
	}
	if(key == X_btn)
	{
		exit(0);
	}
	if(key == LEFT)
	{
		printf("x = %d, y = %d\n", x, y);
	}
	if(key == RIGHT)
	{
		printf("x = %d, y = %d\n", x, y);
	}
}

int	main(int argc, char *argv[])
{
	t_config	config;

	if (argc != 2) {
		write(2, "Usage: ./cub3D <scene_file.cub>\n", 32);
		return 1;
	}
	if (!parse_file(argv[1], &config)) {
		write(2, "Failed to parse the .cub file\n", 31);
		return 1;
	}
	void	*img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 480, "Hello world!");
	img = mlx_new_image(mlx, 100, 100);
	mlx_hook(mlx_win, 2, 1L >> 0, keypress, NULL);
	mlx_hook(mlx_win, 17, 0, keypress, NULL);
	mlx_loop(mlx);
}
