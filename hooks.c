/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:39:34 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:39:37 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == KEY_W)
		move_player(game, game->player.dir_x * 0.3, game->player.dir_y * 0.3);
	if (key == KEY_S)
		move_player(game, -game->player.dir_x * 0.3, -game->player.dir_y * 0.3);
	if (key == KEY_D)
		move_player(game, game->player.plane_x * 0.3, \
					game->player.plane_y * 0.3);
	if (key == KEY_A)
		move_player(game, -game->player.plane_x * 0.3, \
					-game->player.plane_y * 0.3);
	if (key == KEY_LEFT)
		rotate_player(game, -0.1);
	if (key == KEY_RIGHT)
		rotate_player(game, 0.1);
	if (key == KEY_ESC)
		exit(0);
	render_frame(game);
	return (0);
}
