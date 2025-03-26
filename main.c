/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:02 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:40:04 by dukim            ###   ########.fr       */
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
	/* .cub 파일 파싱 (map 모듈) */
	if (!parse_file(argv[1], &game.config))
	{
		write(2, "Failed to parse the .cub file\n", 31);
		exit(1);
	}
	/* 맵 관련 변수 (추후 파싱에 따라 수정) */
	game.map_height = game.config.map_lines;
	game.map_width = 19;
	/* MLX 초기화 */
	game.mlx.mlx = mlx_init();
	game.mlx.win = mlx_new_window(game.mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	/* 이미지와 텍스처 초기화 */
	init_image(&game.img, game.mlx.mlx);
	load_textures(&game.tex, &game.config, game.mlx.mlx);
	mlx_string_put(game.mlx.mlx, game.mlx.win,
		WIDTH / 2 - 20, HEIGHT / 2, 0xFFFFFF, "Press any Key");
	/* 플레이어 초기 설정 */
	set_player_direction('W', &game.player);
	game.player.pos_x = 5.5;
	game.player.pos_y = 5.5;
	/* 이벤트 훅 등록 (키 입력, 윈도우 종료) */
	mlx_hook(game.mlx.win, 2, 1L << 0, keypress, &game);
	mlx_hook(game.mlx.win, 17, 0, keypress, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
