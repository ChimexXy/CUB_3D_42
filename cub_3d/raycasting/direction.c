#include "raycasting.h"

void init_player_direction(t_config *cfg, char spawn_char)
{
    if (spawn_char == 'N') {
        cfg->dir_x = 0.0;
        cfg->dir_y = -1.0;
        cfg->plane_x = 0.66;
        cfg->plane_y = 0.0;
    } else if (spawn_char == 'S') {
        cfg->dir_x = 0.0;
        cfg->dir_y = 1.0;
        cfg->plane_x = -0.66;
        cfg->plane_y = 0.0;
    } else if (spawn_char == 'E') {
        cfg->dir_x = 1.0;
        cfg->dir_y = 0.0;
        cfg->plane_x = 0.0;
        cfg->plane_y = 0.66;
    } else if (spawn_char == 'W') {
        cfg->dir_x = -1.0;
        cfg->dir_y = 0.0;
        cfg->plane_x = 0.0;
        cfg->plane_y = -0.66;
    }
}

