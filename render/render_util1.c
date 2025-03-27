/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:26 by dukim             #+#    #+#             */
/*   Updated: 2025/03/27 19:26:57 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	fill_floor_ceiling(t_game *g)
{
	int	y;
	int	x;
	int	pix;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pix = y * g->img.size_line + x * (g->img.bpp / 8);
			if (y < HEIGHT / 2)
			{
				*(int *)(g->img.data + pix) = \
				(g->config.ceiling_color[0] << 16) | \
				g->config.ceiling_color[1] << 8 | g->config.ceiling_color[2];
			}
			else
			{
				*(int *)(g->img.data + pix) = \
				(g->config.floor_color[0] << 16) | \
				(g->config.floor_color[1] << 8) | (g->config.floor_color[2]);
			}
		}
	}
}

void	init_ray(t_game *g, int x, t_ray *r)
{
	r->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	r->ray_dir_x = g->player.dir_x + \
		g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + \
		g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.pos_x;
	r->map_y = (int)g->player.pos_y;
	if (r->ray_dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->ray_dir_y);
}

void	set_step_and_side_dist(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.pos_x - r->map_x) * \
			r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.pos_x) \
			* r->delta_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.pos_y - r->map_y) * \
			r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.pos_y) \
			* r->delta_y;
	}
}

void	perform_dda(t_game *g, t_ray *r)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= g->map_width || \
			r->map_y < 0 || r->map_y >= g->map_height)
		{
			r->hit = 1;
		}
		else if (g->config.map[r->map_y][r->map_x] != '0')
		{
			r->hit = 1;
		}
	}
}

void	calc_perp_dist(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		r->perp_dist = (r->map_x - g->player.pos_x + \
			(1 - r->step_x) / 2.0) / r->ray_dir_x;
	}
	else
	{
		r->perp_dist = (r->map_y - g->player.pos_y + \
			(1 - r->step_y) / 2.0) / r->ray_dir_y;
	}
}
