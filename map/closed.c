/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:37:57 by dukim             #+#    #+#             */
/*   Updated: 2025/04/23 13:39:20 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** is_on_border: 위치 (i,j)가 맵 테두리에 있는지 검사
*/
int	is_on_border(int i, int j, int height, int width)
{
	if (i == 0 || i == height - 1)
		return (1);
	if (j == 0 || j == width - 1)
		return (1);
	return (0);
}

/*
** has_adjacent_space: 상하좌우 인접 칸이 공백인지 검사
*/
int	has_adjacent_space(t_config *config, int i, int j)
{
	if (config->map[i - 1][j] == ' ')
		return (1);
	if (config->map[i + 1][j] == ' ')
		return (1);
	if (config->map[i][j - 1] == ' ')
		return (1);
	if (config->map[i][j + 1] == ' ')
		return (1);
	return (0);
}
