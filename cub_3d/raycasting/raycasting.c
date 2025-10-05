#include "raycasting.h"

void draw_cell(t_config *cfg, int map_x, int map_y, uint32_t color)
{
    int y;
    int x;
    int px;
    int py;
    
    y = 0;
    px = map_x * CELL;
    py = map_y * CELL;
    while(y < CELL)
    {
        x = 0;
        while(x < CELL)
        {
            mlx_put_pixel(cfg->img, (uint32_t)(px + x), (uint32_t)(py + y), color);
            x++;
        }
        y++;
    }
}

void set_player_position(t_config *cfg)
{
    int y = 0;
    int x = 0;

    while(cfg->map[y])
    {
        x = 0;
        while(cfg->map[y][x])
        {
            char c = cfg->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                cfg->player.x = (double)x + 0.5;
                cfg->player.y = (double)y + 0.5;
				init_player_direction(cfg, c); 
                return;
            }
            x++;
        }
        y++;
    }
}

void draw_player(t_config *cfg)
{
    int px;
    int py;
    int size;
    int y, x;
    int start_x;
    int start_y;
    
    y = 0;
    size = CELL / 3;
    px = (int)(cfg->player.x * CELL);
    py = (int)(cfg->player.y * CELL);
    start_x = px - (size / 2);
    start_y = py - (size / 2);
    
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            mlx_put_pixel(cfg->img, (uint32_t)(start_x + x), (uint32_t)(start_y + y), 0xFF0000FF);
            x++;
        }
        y++;
    }
}

void draw_map(t_config *cfg)
{
    int y;
    int x;
    char c;

    y = 0;
    while(cfg->map[y])
    {
        x = 0;
        while(cfg->map[y][x])
        {
            c = cfg->map[y][x];
            if (c == '1')
                draw_cell(cfg, x, y, 0xAAAAAAFF);
            else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
                draw_cell(cfg, x, y, 0x222222FF);
            x++;
        }
        y++;
    }
}

void render_2d_map(t_config *cfg)
{
    cfg->mlx = mlx_init(WIN_W, WIN_H, "Cub3D", true);
    if (!cfg->mlx)
    {
        printf("Error: MLX init failed\n");
        exit(1);
    }
    
    cfg->img = mlx_new_image(cfg->mlx, WIN_W, WIN_H);
    if (!cfg->img)
    {
        printf("Error: Image creation failed\n");
        exit(1);
    }
    
    mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);
    
    // Initialize player movement flags
    cfg->player.move_up = 0;
    cfg->player.move_down = 0;
    cfg->player.move_left = 0;
    cfg->player.move_right = 0;
    cfg->player.rotate_left = 0;
    cfg->player.rotate_right = 0;
    
    set_player_position(cfg);
    
    mlx_key_hook(cfg->mlx, &handle_keys, cfg);
    mlx_loop_hook(cfg->mlx, &render_frame, cfg);
    
    mlx_loop(cfg->mlx);
    mlx_terminate(cfg->mlx);
}
