/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:39:34 by dukim             #+#    #+#             */
/*   Updated: 2025/03/27 21:57:13 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == KEY_W)
		move_player(game, game->player.dir_x * 0.2, game->player.dir_y * 0.2);
	if (key == KEY_S)
		move_player(game, -game->player.dir_x * 0.2, -game->player.dir_y * 0.2);
	if (key == KEY_D)
		move_player(game, game->player.plane_x * 0.2, \
					game->player.plane_y * 0.2);
	if (key == KEY_A)
		move_player(game, -game->player.plane_x * 0.2, \
					-game->player.plane_y * 0.2);
	if (key == KEY_LEFT)
		rotate_player(game, -0.1);
	if (key == KEY_RIGHT)
		rotate_player(game, 0.1);
	if (key == KEY_ESC)
		exit(0);
	render_frame(game);
	return (0);
}

int	close_win(void)
{
	exit(0);
}
