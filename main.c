/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:02 by dukim             #+#    #+#             */
/*   Updated: 2025/03/27 21:53:25 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <scene_file.cub>\n", 32);
		exit(1);
	}
	if (!parse_file(argv[1], &game.config))
	{
		write(2, "Error\nFailed to parse the .cub file\n", 31);
		exit(1);
	}
	game.map_height = game.config.map_height;
	game.map_width = game.config.map_width;
	game.mlx.mlx = mlx_init();
	game.mlx.win = mlx_new_window(game.mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	init_image(&game.img, game.mlx.mlx);
	load_textures(&game.tex, &game.config, game.mlx.mlx);
	mlx_string_put(game.mlx.mlx, game.mlx.win,
		WIDTH / 2 - 20, HEIGHT / 2, 0xFFFFFF, "Press any Key");
	/* 플레이어 초기 설정 */
	game.player.pos_x = (double)game.config.player.x + 0.5;
	game.player.pos_y = (double)game.config.player.y + 0.5;
	set_player_direction(game.config.player.sight, &game.player);
	mlx_hook(game.mlx.win, 2, 1L << 0, keypress, &game);
	mlx_hook(game.mlx.win, 17, 0, keypress, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
