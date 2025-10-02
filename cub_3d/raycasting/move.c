#include "raycasting.h"

#define MOVE_SPEED 0.05

void handle_keys(mlx_key_data_t keydata, void *param)
{
    t_config *cfg = (t_config *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(cfg->mlx);
    
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W)
            cfg->player.move_up = 1;
        if (keydata.key == MLX_KEY_S)
            cfg->player.move_down = 1;
        if (keydata.key == MLX_KEY_A)
            cfg->player.move_left = 1;
        if (keydata.key == MLX_KEY_D)
            cfg->player.move_right = 1;
    }

    if (keydata.action == MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_W)
            cfg->player.move_up = 0;
        if (keydata.key == MLX_KEY_S)
            cfg->player.move_down = 0;
        if (keydata.key == MLX_KEY_A)
            cfg->player.move_left = 0;
        if (keydata.key == MLX_KEY_D)
            cfg->player.move_right = 0;
    }
}

int is_wall(t_config *cfg, double x, double y)
{
    double player_radius = 1.0 / 6.0;
    double margin = player_radius * 0.5;
    
    double corners[4][2] = {
        {x - margin, y - margin},
        {x + margin, y - margin},
        {x - margin, y + margin},
        {x + margin, y + margin}
    };
    
    int i = 0;
    while (i < 4)
    {
        double check_x = corners[i][0];
        double check_y = corners[i][1];
        
        int map_x = (int)check_x;
        int map_y = (int)check_y;
        
        if (map_y < 0 || map_x < 0)
            return (1);
        
        if (!cfg->map[map_y])
            return (1);
        
        if (!cfg->map[map_y][map_x])
            return (1);
        
        if (cfg->map[map_y][map_x] == '1')
            return (1);
        
        i++;
    }
    
    return (0);
}

void update_player_position(t_config *cfg)
{
    double new_x = cfg->player.x;
    double new_y = cfg->player.y;
    
    if (cfg->player.move_up)
        new_y -= MOVE_SPEED;
    if (cfg->player.move_down)
        new_y += MOVE_SPEED;
    if (cfg->player.move_left)
        new_x -= MOVE_SPEED;
    if (cfg->player.move_right)
        new_x += MOVE_SPEED;
    
    if (!is_wall(cfg, new_x, cfg->player.y))
        cfg->player.x = new_x;
    if (!is_wall(cfg, cfg->player.x, new_y))
        cfg->player.y = new_y;
}

void render_frame(void *param)
{
    t_config *cfg = (t_config *)param;
    
    update_player_position(cfg);
    draw_map(cfg);
    draw_player(cfg);
}