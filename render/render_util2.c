/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:29 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:40:31 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	calc_draw_params(t_ray *r)
{
	r->line_height = (int)(HEIGHT / r->perp_dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

void	calc_wall_tex(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		r->wall_x = g->player.pos_y + r->perp_dist * \
			r->ray_dir_y;
	}
	else
	{
		r->wall_x = g->player.pos_x + r->perp_dist * \
			r->ray_dir_x;
	}
	r->wall_x = r->wall_x - floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * g->tex.width);
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			r->tex_x = g->tex.width - r->tex_x - 1;
	}
	if (r->side == 1)
	{
		if (r->ray_dir_y < 0)
			r->tex_x = g->tex.width - r->tex_x - 1;
	}
}

void	calc_texture_params(t_game *g, t_ray *r)
{
	r->step = (1.0 * g->tex.height) / r->line_height;
	r->tex_pos = (r->draw_start - HEIGHT / 2 + \
		r->line_height / 2) * r->step;
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			r->tex_num = 1;
		else
			r->tex_num = 2;
	}
	else
	{
		if (r->ray_dir_y > 0)
			r->tex_num = 3;
		else
			r->tex_num = 0;
	}
}

void	draw_stripe(t_game *g, int x, t_ray *r)
{
	int	y;
	int	pix;
	int	color;
	int	tex_y;

	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex_y = (int)r->tex_pos & (g->tex.height - 1);
		r->tex_pos = r->tex_pos + r->step;
		color = *(int *)(g->tex.tex_data[r->tex_num] + \
			(tex_y * g->tex.size_line[r->tex_num]) + \
			(r->tex_x * (g->tex.bpp[r->tex_num] / 8)));
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		pix = y * g->img.size_line + \
			x * (g->img.bpp / 8);
		*(int *)(g->img.data + pix) = color;
		y++;
	}
}
