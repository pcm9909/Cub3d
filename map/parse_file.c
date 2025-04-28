/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:12 by dukim             #+#    #+#             */
/*   Updated: 2025/03/27 21:55:00 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** check_extension: 파일 이름이 ".cub" 확장자로 끝나면 1, 아니면 0을 반환.
*/
static int	check_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	_init(const char *filename, t_config *config)
{
	int		fd;

	if (!check_extension(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	init_config(config);
	return (fd);
}

/*
 * parse_file: 지정한 파일(예: "scene.cub")을 열어 한 줄씩 읽으면서
 * 텍스처 경로, 바닥/천장 색상, 그리고 맵 정보를 config 구조체에 저장합니다.
 */
int	parse_file(const char *filename, t_config *config)
{
	int		fd;
	char	*line;

	fd = _init(filename, config);
	if (!fd)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		remove_trailing_newline(line);
		if (!process_line(config, line))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!validate_player_spawn(&(config->player)))
		return (0);
	if (config->map_height == 0 || !validate_map_closed(config))
		return (0);
	return (1);
}
