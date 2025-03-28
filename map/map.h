/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:08 by dukim             #+#    #+#             */
/*   Updated: 2025/03/27 21:54:51 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <fcntl.h>

# include "../cub3d.h"

void	init_config(t_config *config);
void	free_config(t_config *config);

char	*ltrim(char *s);
void	remove_trailing_newline(char *s);

int		process_line(t_config *config, char *line);
int		parse_file(const char *filename, t_config *config);

#endif
