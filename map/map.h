#ifndef MAP_H
# define MAP_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../libft/libft.h"

/*
 * 예제 구조체 t_config는 .cub 파일에 포함될 주요 요소를 저장합니다.
 * - texture_*: 각각 북, 남, 서, 동 방향의 텍스처 파일 경로
 * - floor_color, ceiling_color: 각각 R,G,B값 (0~255)
 * - map: 파일의 마지막 부분에 등장하는 맵 문자열 배열
 * - map_lines: 맵이 몇 줄인지 저장
 */
typedef struct s_config {
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;// 변환된 int 맵
	int		map_lines;
} t_config;

void    init_config(t_config *config);
void    free_config(t_config *config);

char    *ltrim(char *s);
void    remove_trailing_newline(char *s);

int     process_line(t_config *config, char *line);
int     parse_file(const char *filename, t_config *config);

#endif