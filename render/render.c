/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:17 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:40:18 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	render_frame(t_game *g)
{
	int		x;
	t_ray	r;

	fill_floor_ceiling(g);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(g, x, &r);
		set_step_and_side_dist(g, &r);
		perform_dda(g, &r);
		calc_perp_dist(g, &r);
		calc_draw_params(&r);
		calc_wall_tex(g, &r);
		calc_texture_params(g, &r);
		draw_stripe(g, x, &r);
		x++;
	}
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win,
		g->img.img, 0, 0);
	return (0);
}
