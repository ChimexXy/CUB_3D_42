#ifndef RAYCASTING_H
#define RAYCASTING_H

#define MOVE_SPEED 0.05
#define WIN_W 800
#define WIN_H 600
#define CELL 50   // size of 1 map cell in pixels


#include "./../cub3d.h"

void render_2d_map(t_config *cfg);
void draw_map(t_config *cfg);
void draw_player(t_config *cfg);
void handle_keys(mlx_key_data_t keydata, void *param);
void render_frame(void *param);

#endif