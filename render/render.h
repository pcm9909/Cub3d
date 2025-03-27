/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:40:57 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:40:59 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../cub3d.h"

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_num;
}	t_ray;

void	fill_floor_ceiling(t_game *g);
void	init_ray(t_game *g, int x, t_ray *r);
void	set_step_and_side_dist(t_game *g, t_ray *r);
void	perform_dda(t_game *g, t_ray *r);
void	calc_perp_dist(t_game *g, t_ray *r);
void	calc_draw_params(t_ray *r);
void	calc_wall_tex(t_game *g, t_ray *r);
void	calc_texture_params(t_game *g, t_ray *r);
void	draw_stripe(t_game *g, int x, t_ray *r);

#endif
