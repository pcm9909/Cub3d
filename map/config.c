#include "map.h"

void init_config(t_config *config)
{
    config->texture_no = NULL;
    config->texture_so = NULL;
    config->texture_we = NULL;
    config->texture_ea = NULL;
    config->floor_color[0] = config->floor_color[1] =
    config->floor_color[2] = -1;
    config->ceiling_color[0] = config->ceiling_color[1] =
    config->ceiling_color[2] = -1;
    config->map = NULL;
    config->map_lines = 0;
}

void free_config(t_config *config)
{
    if (config->texture_no)
        free(config->texture_no);
    if (config->texture_so)
        free(config->texture_so);
    if (config->texture_we)
        free(config->texture_we);
    if (config->texture_ea)
        free(config->texture_ea);
    if (config->map)
    {
        for (int i = 0; i < config->map_lines; i++)
            free(config->map[i]);
        free(config->map);
    }
}
