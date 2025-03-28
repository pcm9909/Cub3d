/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:04 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:41:06 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	init_config(t_config *config)
{
	config->texture_no = NULL;
	config->texture_so = NULL;
	config->texture_we = NULL;
	config->texture_ea = NULL;
	config->floor_color[0] = -1;
	config->floor_color[1] = -1;
	config->floor_color[2] = -1;
	config->ceiling_color[0] = -1;
	config->ceiling_color[1] = -1;
	config->ceiling_color[2] = -1;
	config->map = NULL;
	config->map_height = 0;
	config->map_width = 0;
	config->player.x = -1;
	config->player.y = -1;
	config->player.sight = '\0';
}

void	free_config(t_config *config)
{
	int	i;

	if (config->texture_no)
		free(config->texture_no);
	if (config->texture_so)
		free(config->texture_so);
	if (config->texture_we)
		free(config->texture_we);
	if (config->texture_ea)
		free(config->texture_ea);
	if (config->map)
	{
		i = 0;
		while (i < config->map_height)
		{
			free(config->map[i]);
			i++;
		}
		free(config->map);
	}
}
