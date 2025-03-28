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
 * parse_file: 지정한 파일(예: "scene.cub")을 열어 한 줄씩 읽으면서
 * 텍스처 경로, 바닥/천장 색상, 그리고 맵 정보를 config 구조체에 저장합니다.
 */
int	parse_file(const char *filename, t_config *config)
{
	int		fd;
	char	*line;

	if (!validate_extension(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	init_config(config);
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
	return (1);
}
