/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:08 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:40:09 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	int	new_x;
	int	current_y;
	int	new_y;
	int	current_x;

	new_x = (int)(game->player.pos_x + move_x);
	current_y = (int)(game->player.pos_y);
	if (new_x >= 0 && new_x < game->map_width && \
		current_y >= 0 && current_y < game->map_height && \
		game->config.map[current_y][new_x] == '0')
		game->player.pos_x += move_x;
	new_y = (int)(game->player.pos_y + move_y);
	current_x = (int)(game->player.pos_x);
	if (new_y >= 0 && new_y < game->map_height && \
		current_x >= 0 && current_x < game->map_width && \
		game->config.map[new_y][current_x] == '0')
		game->player.pos_y += move_y;
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle) - \
		game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + \
		game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle) - \
		game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + \
		game->player.plane_y * cos(angle);
}

void	set_player_direction(char dir, t_player *player)
{
	int		index;
	double	directions[4][4] = {
		{0, -1, 0.66, 0},
		{0, 1, -0.66, 0},
		{1, 0, 0, 0.66},
		{-1, 0, 0, -0.66}
	};

	if (dir == 'N')
		index = 0;
	else if (dir == 'S')
		index = 1;
	else if (dir == 'E')
		index = 2;
	else if (dir == 'W')
		index = 3;
	else
		index = 0;
	player->dir_x = directions[index][0];
	player->dir_y = directions[index][1];
	player->plane_x = directions[index][2];
	player->plane_y = directions[index][3];
}
