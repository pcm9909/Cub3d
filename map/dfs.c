/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:37:57 by dukim             #+#    #+#             */
/*   Updated: 2025/03/28 22:03:01 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
** is_valid_index: (i, j)가 config->map 내에서 유효한 인덱스인지 검사.
** 유효하면 1, 아니면 0 반환.
*/
int	is_valid_index(int i, int j, t_config *config)
{
	int	row_len;

	if (i < 0 || i >= config->map_height)
		return (0);
	row_len = ft_strlen(config->map[i]);
	if (j < 0 || j >= row_len)
		return (0);
	return (1);
}

/*
** dfs: (i, j) 위치에서 시작하여 연결된 '0' 영역을 DFS로 탐색합니다.
** 만약 탐색 중에 셀이 out-of-bound이거나, 해당 행의 길이를 초과하거나,
** 또는 셀이 공백(' ')인데 그 공백이 행의 시작/끝 또는 인접 행의 길이 부족이면
** 열린 영역으로 판단하여 0을 반환합니다.
** 내부 공백(경계가 아닌)은 벽으로 취급합니다.
*/
int	dfs(int i, int j, t_config *config, int **visited)
{
	int	row_len;

	if (!is_valid_index(i, j, config))
		return (0);
	row_len = ft_strlen(config->map[i]);
	if (config->map[i][j] == ' ')
	{
		if (i == 0 || i == config->map_height - 1 || \
			j == 0 || j == row_len - 1 || \
			(int)ft_strlen(config->map[i - 1]) < j || \
			(int)ft_strlen(config->map[i + 1]) < j)
			return (0);
		return (1);
	}
	if (config->map[i][j] != '0' || visited[i][j])
		return (1);
	visited[i][j] = 1;
	if (!dfs(i - 1, j, config, visited) || \
		!dfs(i + 1, j, config, visited) || \
		!dfs(i, j - 1, config, visited) || \
		!dfs(i, j + 1, config, visited))
		return (0);
	return (1);
}

/*
** allocate_visited: config->map 크기에 맞춰 visited 배열을 동적 할당.
** 할당에 실패하면 NULL 반환.
*/
int	**allocate_visited(t_config *config)
{
	int		**visited;
	int		i;
	int		row_len;

	visited = malloc(sizeof(int *) * config->map_height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < config->map_height)
	{
		row_len = ft_strlen(config->map[i]);
		visited[i] = ft_calloc(row_len, sizeof(int));
		if (!visited[i])
		{
			while (i-- >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

/*
** free_visited: allocate_visited로 할당한 visited 배열 해제.
*/
void	free_visited(int map_height, int **visited)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
