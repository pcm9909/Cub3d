/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:14 by dukim             #+#    #+#             */
/*   Updated: 2025/03/29 18:21:49 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** check_player_spawn: 한 줄에서 'N', 'S', 'E', 'W' 문자가 있다면,
** 플레이어 스폰이 아직 기록되지 않은 경우에만 해당 좌표와 시선을
** config->player에 저장하고 해당 위치를 '0'으로 변경합니다.
** 만약 이미 플레이어 스폰이 기록되어 있다면 에러(0)를 반환합니다.
*/
int	check_player_spawn(t_config *config, char *line, int row)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || \
			line[i] == 'E' || line[i] == 'W')
		{
			if (config->player.sight != '\0')
				return (0);
			config->player.x = i;
			config->player.y = row;
			config->player.sight = line[i];
			line[i] = '0';
		}
		i++;
	}
	return (1);
}

/*
 * process_color_line: 'F' 또는 'C'로 시작하는 라인을 처리하여
 * 해당 색상 배열에 "R,G,B" 값을 저장합니다.
 * 성공하면 1, 실패하면 0을 반환합니다.
 */
static int	process_color(t_config *config, char type, char *line)
{
	char	**token;
	char	*color_line;
	int		i;
	int		ret;

	color_line = ft_strdup(ltrim(line + 1));
	token = ft_split(color_line, ',');
	i = 0;
	while (token && i < 3)
	{
		if (type == 'F')
		{
			config->floor_color[i] = ft_atoi(token[i]);
		}
		else if (type == 'C')
			config->ceiling_color[i] = ft_atoi(token[i]);
		i++;
	}
	ft_freesplit(token);
	free(color_line);
	ret = (i == 3);
	return (ret);
}

/*
 * process_texture: 텍스처 정의 라인을 처리.
 */
static int	process_texture(t_config *config, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (config->texture_no != NULL)
			return (0);
		config->texture_no = ft_strdup(ltrim(line + 2));
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (config->texture_so != NULL)
			return (0);
		config->texture_so = ft_strdup(ltrim(line + 2));
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (config->texture_we != NULL)
			return (0);
		config->texture_we = ft_strdup(ltrim(line + 2));
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (config->texture_ea != NULL)
			return (0);
		config->texture_ea = ft_strdup(ltrim(line + 2));
	}
	return (1);
}

/*
 * add_map_line: config->map 배열에 한 줄 추가하고, map_width와 플레이어 좌표를 갱신.
 */
static int	add_map_line(t_config *config, char *line)
{
	char	**new_map;
	int		len;

	if (!validate_map_line(line))
		return (0);
	len = ft_strlen(line);
	if (len > config->map_width)
		config->map_width = len;
	if (!check_player_spawn(config, line, config->map_height))
		return (0);
	new_map = ft_realloc(config->map, \
			(sizeof(char *) * config->map_height), \
			(sizeof(char *) * (config->map_height + 1)));
	if (!new_map)
		return (0);
	config->map = new_map;
	config->map[config->map_height] = ft_strdup(line);
	config->map_height++;
	return (1);
}

/*
 * process_line: .cub 파일의 한 줄을 처리 (텍스처, 색상, 맵 정보 분기).
 */
int	process_line(t_config *config, char *line)
{
	static int	elements;

	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 || \
		ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		elements++;
		if (!process_texture(config, line))
			return (0);
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		elements++;
		if (!validate_color_line(line))
			return (0);
		if (!process_color(config, line[0], line))
			return (0);
	}
	else if (line[0] != '\0')
	{
		if (elements != 6)
			return (0);
		if (!add_map_line(config, line))
			return (0);
	}
	return (1);
}
