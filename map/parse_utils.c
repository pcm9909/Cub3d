/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:14 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:41:15 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * parse_color_str: "R,G,B" 형태의 문자열을 파싱하여 정수 배열에 저장
 * 반환값은 3개의 값 모두 파싱되었으면 1, 아니면 0을 반환합니다.
 */
static int	parse_color_str(char *str, int color[3])
{
	char	**token;
	int		i;

	i = 0;
	token = ft_split(str, ',');
	while (token && i < 3)
	{
		color[i] = atoi(token[i]);
		i++;
	}
	ft_freesplit(token);
	return (i == 3);
}

/*
 * add_map_line: config->map 배열에 한 줄씩 추가합니다.
 */
static int	add_map_line(t_config *config, char *line)
{
	char	**new_map;

	new_map = ft_realloc(config->map, sizeof(char *) * (config->map_lines + 1));
	if (!new_map)
		return (0);
	config->map = new_map;
	config->map[config->map_lines] = ft_strdup(line);
	config->map_lines++;
	return (1);
}

/*
 * process_texture: 텍스처 정의 라인을 처리합니다.
 * "NO", "SO", "WE", "EA"로 시작하는 경우,
 * 접두사 이후의 경로 문자열을 config에 저장합니다.
 * 성공하면 1, 실패하면 0을 반환합니다.
 */
static int	process_texture(t_config *config, char *trimmed)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		config->texture_no = ft_strdup(ltrim(trimmed + 2));
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		config->texture_so = ft_strdup(ltrim(trimmed + 2));
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		config->texture_we = ft_strdup(ltrim(trimmed + 2));
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		config->texture_ea = ft_strdup(ltrim(trimmed + 2));
	else
		return (0);
	return (1);
}

/*
 * process_color: 색상 정의 라인을 처리합니다.
 * 'F' (바닥) 또는 'C' (천장)로 시작하는 경우,
 * 접두사 이후의 색상 문자열을 파싱하여 config의 색상 배열에 저장합니다.
 * 성공하면 1, 실패하면 0을 반환합니다.
 */
static int	process_color(t_config *config, char type, char *trimmed)
{
	char	*color_line;
	int		ret;

	color_line = ft_strdup(ltrim(trimmed + 1));
	ret = 0;
	if (type == 'F')
		ret = parse_color_str(color_line, config->floor_color);
	else if (type == 'C')
		ret = parse_color_str(color_line, config->ceiling_color);
	free(color_line);
	return (ret);
}

/*
 * process_line: .cub 파일의 한 줄을 처리합니다.
 * 텍스처, 색상 정의, 혹은 맵 정보에 따라 분기하여 처리합니다.
 * 각 하위 처리는 위의 process_texture, process_color, add_map_line 함수를 호출합니다.
 * 성공하면 1, 실패하면 0을 반환합니다.
 */
int	process_line(t_config *config, char *line)
{
	char	*trimmed;

	trimmed = ltrim(line);
	if (ft_strncmp(trimmed, "NO", 2) == 0 || \
		ft_strncmp(trimmed, "SO", 2) == 0 || \
		ft_strncmp(trimmed, "WE", 2) == 0 || \
		ft_strncmp(trimmed, "EA", 2) == 0)
	{
		if (!process_texture(config, trimmed))
			return (0);
	}
	else if (trimmed[0] == 'F' || trimmed[0] == 'C')
	{
		if (!process_color(config, trimmed[0], trimmed))
			return (0);
	}
	else if (trimmed[0] != '\0')
	{
		if (!add_map_line(config, trimmed))
			return (0);
	}
	return (1);
}
