/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:36:13 by dukim             #+#    #+#             */
/*   Updated: 2025/03/28 18:36:15 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** validate_extension: 파일 이름이 ".cub" 확장자로 끝나면 1, 아니면 0을 반환.
*/
int	validate_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

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
