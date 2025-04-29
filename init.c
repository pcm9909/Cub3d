/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:39:57 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:39:59 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_img *img, void *mlx)
{
	img->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img->data = mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_line, &img->endian);
}

void	load_textures(t_tex *tex, t_config *config, void *mlx)
{
	char	*texture_files[4];
	int		i;

	texture_files[0] = config->texture_so;
	texture_files[1] = config->texture_ea;
	texture_files[2] = config->texture_we;
	texture_files[3] = config->texture_no;
	tex->width = 64;
	tex->height = 64;
	i = 0;
	while (i < 4)
	{
		tex->tex_img[i] = mlx_xpm_file_to_image(mlx, texture_files[i], \
				&tex->width, &tex->height);
		if (!tex->tex_img[i])
		{
			write(2, "Error\nFailed to load texture\n", 30);
			exit(1);
		}
		else
			tex->tex_data[i] = mlx_get_data_addr(tex->tex_img[i], \
					&tex->bpp[i], &tex->size_line[i], &tex->endian[i]);
		i++;
	}
}
