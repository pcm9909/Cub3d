/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:58:15 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:58:16 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "mlx/mlx.h"
# include "libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

/* 키코드 (linux 기준) */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_player_spawn
{
	int		x;
	int		y;
	char	sight;
}	t_player_spawn;

typedef struct s_config {
	char			*texture_no;
	char			*texture_so;
	char			*texture_we;
	char			*texture_ea;
	int				floor_color[3];
	int				ceiling_color[3];
	char			**map;
	int				map_height;
	int				map_width;
	t_player_spawn	player;
}	t_config;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*tex_img[4];
	char	*tex_data[4];
	int		bpp[4];
	int		size_line[4];
	int		endian[4];
	int		width;
	int		height;
}	t_tex;

typedef struct s_game
{
	t_config	config;
	t_player	player;
	t_mlx		mlx;
	t_img		img;
	t_tex		tex;
	int			map_width;
	int			map_height;
}	t_game;

/* 초기화 및 파싱 */
int		parse_file(const char *filename, t_config *config);

/* MLX 관련 초기화 */
void	init_image(t_img *img, void *mlx);
void	load_textures(t_tex *tex, t_config *config, void *mlx);

/* 플레이어 관련 */
void	set_player_direction(char dir, t_player *player);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double angle);

/* 렌더링 및 이벤트 */
int		render_frame(t_game *game);
int		keypress(int key, void *param);

#endif
