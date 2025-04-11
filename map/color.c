/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:09:56 by dukim             #+#    #+#             */
/*   Updated: 2025/04/11 18:09:57 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** get_color_type: 라인이 정확히 'F ' 또는 'C '로 시작하면 그 문자를 반환, 
** 아니라면 0을 반환합니다.
*/
char	get_color_type(const char *line)
{
	if (!line)
		return (0);
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		return (line[0]);
	return (0);
}

/*
** get_color_values: color 라인의 접두사('F ' 또는 'C ') 이후의 문자열을
** 좌우 공백 제거(trim) 후 복사하여 반환합니다.
*/
char	*get_color_values(const char *line)
{
	char	*temp;
	char	*trimmed;

	temp = ft_strdup(line + 2);
	if (!temp)
		return (NULL);
	trimmed = ft_strtrim(temp, " \t");
	free(temp);
	return (trimmed);
}

/*
** validate_color_token: 개별 토큰을 좌우 공백 제거 후, 
** 빈 문자열이 아니고 모든 문자가 숫자인지, 그리고 값이 0~255 범위인지 검사합니다.
*/
int	validate_color_token(const char *token)
{
	char	*t;
	int		i;
	int		value;

	t = ft_strtrim(token, " \t");
	if (!t || t[0] == '\0')
	{
		free(t);
		return (0);
	}
	i = 0;
	while (t[i])
	{
		if (!ft_isdigit(t[i]))
		{
			free(t);
			return (0);
		}
		i++;
	}
	value = ft_atoi(t);
	free(t);
	if (value < 0 || value > 255)
		return (0);
	return (1);
}

/*
** validate_color_tokens: tokens 배열에 담긴 토큰 개수가 정확히 3개이고,
** 각 토큰이 유효한지를 검사합니다.
*/
int	validate_color_tokens(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		count++;
		i++;
	}
	if (count != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!validate_color_token(tokens[i]))
			return (0);
		i++;
	}
	return (1);
}
