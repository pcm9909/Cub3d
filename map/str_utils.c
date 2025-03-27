/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:15 by dukim             #+#    #+#             */
/*   Updated: 2025/03/26 19:41:17 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/* 좌측 공백 제거 */
char	*ltrim(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

/* 
 * remove_trailing_newline: 문자열의 마지막에 개행 문자('\n')가 있으면 제거
 */
void	remove_trailing_newline(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}
