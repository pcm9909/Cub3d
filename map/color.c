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

/* 현재 위치에서 0~255 숫자 하나 읽어서 color[idx]에 저장 */
static int	parse_component(const char *s, int *i, int *dst)
{
	int	val;
	int	len;

	val = 0;
	len = 0;
	while (ft_isdigit(s[*i]))
	{
		val = val * 10 + (s[*i] - '0');
		(*i)++;
		len++;
		if (len > 3)
			return (0);
	}
	if (len == 0 || val > 255)
		return (0);
	*dst = val;
	return (1);
}

/* "R,G,B" 형태 전체 검증 + 추출 */
int	parse_rgb(const char *raw, int color[3])
{
	int	i;
	int	part;

	i = 1;
	part = 0;
	if (raw[0] != ' ')
		return (0);
	while (part < 3)
	{
		if (!parse_component(raw, &i, &color[part]))
			return (0);
		part++;
		if (part < 3)
		{
			if (raw[i++] != ',')
				return (0);
		}
	}
	return (raw[i] == '\0');
}
