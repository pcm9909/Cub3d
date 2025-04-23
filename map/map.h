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

char	get_color_type(const char *line);
char	*get_color_values(const char *line);
int		validate_color_token(const char *token);
int		validate_color_tokens(char **tokens);

int		is_on_border(int i, int j, int height, int width);
int		has_adjacent_space(t_config *config, int i, int j);

int		validate_extension(const char *filename);
int		validate_map_line(char *line);
int		validate_player_spawn(t_player_spawn *player);
int		validate_color_line(const char *line);
int		validate_map_closed(t_config *config);

#endif
