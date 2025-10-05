#ifndef RAYCASTING_H
#define RAYCASTING_H

#define MOVE_SPEED 0.02
#define ROT_SPEED 0.015
#define WIN_W 1920
#define WIN_H 1080
#define CELL 40   // size of 1 map cell in pixels


#include "./../cub3d.h"
#include <math.h>
#include <string.h>

void render_2d_map(t_config *cfg);
void draw_map(t_config *cfg);
void draw_player(t_config *cfg);
void handle_keys(mlx_key_data_t keydata, void *param);
void render_frame(void *param);
void init_player_direction(t_config *cfg, char spawn_char);

void raycasting(t_config *cfg);
void draw_rays_on_minimap(t_config *cfg);
void draw_vertical_line(t_config *cfg, int x, int start, int end, uint32_t color);
void draw_thick_line(t_config *cfg, double start_x, double start_y, double end_x, double end_y, uint32_t color, int thickness);
void draw_line(t_config *cfg, double start_x, double start_y, double end_x, double end_y, uint32_t color);
#endif