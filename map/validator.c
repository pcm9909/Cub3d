/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:36:13 by dukim             #+#    #+#             */
/*   Updated: 2025/03/28 22:02:57 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** validate_map_line: 맵 라인에 허용된 문자('0', '1', 'N', 'S', 'E', 'W')만
** 포함되어 있는지 검사합니다. 허용되지 않은 문자가 있으면 0, 
** 모두 허용되면 1을 반환합니다.
*/
int	validate_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && \
			line[i] != ' ' && \
			line[i] != 'N' && line[i] != 'S' && \
			line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

/*
** validate_player_spawn: 플레이어 초기 위치가 존재하는 지 검증합니다.
*/
int	validate_player_spawn(t_player_spawn *player)
{
	if (player->x == -1 && player->y == -1 && \
		player->sight == '\0')
		return (0);
	return (1);
}

/*
** validate_map_closed: 맵 전체의 모든 '0' 영역이 완전히 닫혀 있는지 검사.
** 만약 하나라도 열린 영역이 있으면 0, 모두 닫혀 있으면 1 반환.
*/
int	validate_map_closed(t_config *config)
{
	int	i;
	int	j;
	int	h;
	int	w;

	h = config->map_height;
	i = 0;
	while (i < h)
	{
		w = ft_strlen(config->map[i]);
		j = 0;
		while (j < w)
		{
			if (config->map[i][j] == '0')
			{
				if (is_on_border(i, j, h, w) || \
					has_adjacent_space(config, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
