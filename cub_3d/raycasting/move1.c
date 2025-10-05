#include "raycasting.h"

void draw_vertical_line(t_config *cfg, int x, int start, int end, uint32_t color)
{
    int y;

    y = start;
    while (y <= end)
    {
        mlx_put_pixel(cfg->img, x, y, color);
        y++;
    }
}

void raycasting(t_config *cfg)
{
    int x;
    
    // Allocate rays array if not already allocated
    if (!cfg->rays)
    {
        cfg->num_rays = WIN_W;
        cfg->rays = malloc(sizeof(t_ray) * cfg->num_rays);
    }
    
    for (x = 0; x < WIN_W; x++)
    {
        // Store ray start position (player position)
        cfg->rays[x].start_x = cfg->player.x;
        cfg->rays[x].start_y = cfg->player.y;
        
        // Calculate ray position and direction
        double camera_x = 2 * x / (double)WIN_W - 1;
        double ray_dir_x = cfg->dir_x + cfg->plane_x * camera_x;
        double ray_dir_y = cfg->dir_y + cfg->plane_y * camera_x;
        
        // Store ray direction
        cfg->rays[x].angle = atan2(ray_dir_y, ray_dir_x);
        
        // Which box of the map we're in
        int map_x = (int)cfg->player.x;
        int map_y = (int)cfg->player.y;
        
        // Length of ray from one side to next side
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
        
        double perp_wall_dist;
        double side_dist_x;
        double side_dist_y;
        
        int step_x;
        int step_y;
        int hit = 0;
        int side;
        
        // Calculate step and initial sideDist
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (cfg->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - cfg->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (cfg->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - cfg->player.y) * delta_dist_y;
        }
        
        // Perform DDA
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            
            // Check if ray hit a wall
            if (map_y < 0 || map_x < 0 || !cfg->map[map_y] || !cfg->map[map_y][map_x])
                hit = 1;
            else if (cfg->map[map_y][map_x] == '1')
                hit = 1;
        }
        
        // Calculate distance and end point for ray visualization
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);
        
        // Store ray end position (wall hit position)
        cfg->rays[x].end_x = cfg->player.x + ray_dir_x * perp_wall_dist;
        cfg->rays[x].end_y = cfg->player.y + ray_dir_y * perp_wall_dist;
        
        // ... rest of your 3D rendering code (line height calculation, drawing, etc.)
        int line_height = (int)(WIN_H / perp_wall_dist);
        int draw_start = -line_height / 2 + WIN_H / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WIN_H / 2;
        if (draw_end >= WIN_H) draw_end = WIN_H - 1;
        
        uint32_t color;
        if (side == 1)
            color = 0x888888FF;
        else
            color = 0xCCCCCCFF;
        
        draw_vertical_line(cfg, x, draw_start, draw_end, color);
    }
}

void draw_rays_on_minimap(t_config *cfg)
{
    int i;
    double scale = CELL;  // Scale factor for minimap
    
    // Draw only every Nth ray to avoid clutter (adjust as needed)
    int ray_step = cfg->num_rays / 60;  // Draw ~60 rays
    
    if (ray_step < 1) ray_step = 1;
    
    for (i = 0; i < cfg->num_rays; i += ray_step)
    {
        if (!cfg->rays) break;
        
        double start_x = cfg->rays[i].start_x * scale;
        double start_y = cfg->rays[i].start_y * scale;
        double end_x = cfg->rays[i].end_x * scale;
        double end_y = cfg->rays[i].end_y * scale;
        
        // Draw ray line using Bresenham's line algorithm
        draw_line(cfg, start_x, start_y, end_x, end_y, 0xFF0000FF);
    }
    
    // Draw player direction line (thicker and different color)
    double dir_end_x = cfg->player.x * scale + cfg->dir_x * 20;
    double dir_end_y = cfg->player.y * scale + cfg->dir_y * 20;
    draw_thick_line(cfg, cfg->player.x * scale, cfg->player.y * scale, 
                   dir_end_x, dir_end_y, 0x00FF00FF, 2);
}

// Bresenham's line algorithm for drawing lines
void draw_line(t_config *cfg, double start_x, double start_y, double end_x, double end_y, uint32_t color)
{
    int x0 = (int)start_x;
    int y0 = (int)start_y;
    int x1 = (int)end_x;
    int y1 = (int)end_y;
    
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (1)
    {
        // Only draw if within image bounds
        if (x0 >= 0 && x0 < (int)cfg->img->width && y0 >= 0 && y0 < (int)cfg->img->height)
        {
            mlx_put_pixel(cfg->img, x0, y0, color);
        }
        
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
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
    
    // Rotation
    if (cfg->player.rotate_right)
    {
		double old_dir_x = cfg->dir_x;
		cfg->dir_x = cfg->dir_x * cos(ROT_SPEED) - cfg->dir_y * sin(ROT_SPEED);
		cfg->dir_y = old_dir_x * sin(ROT_SPEED) + cfg->dir_y * cos(ROT_SPEED);
		double old_plane_x = cfg->plane_x;
		cfg->plane_x = cfg->plane_x * cos(ROT_SPEED) - cfg->plane_y * sin(ROT_SPEED);
		cfg->plane_y = old_plane_x * sin(ROT_SPEED) + cfg->plane_y * cos(ROT_SPEED);
	}
    if (cfg->player.rotate_left)
    {
		double old_dir_x = cfg->dir_x;
		cfg->dir_x = cfg->dir_x * cos(-ROT_SPEED) - cfg->dir_y * sin(-ROT_SPEED);
		cfg->dir_y = old_dir_x * sin(-ROT_SPEED) + cfg->dir_y * cos(-ROT_SPEED);
		double old_plane_x = cfg->plane_x;
		cfg->plane_x = cfg->plane_x * cos(-ROT_SPEED) - cfg->plane_y * sin(-ROT_SPEED);
		cfg->plane_y = old_plane_x * sin(-ROT_SPEED) + cfg->plane_y * cos(-ROT_SPEED);
    }

    // Movement
    if (cfg->player.move_up)
    {
        new_x += cfg->dir_x * MOVE_SPEED;
        new_y += cfg->dir_y * MOVE_SPEED;
    }
    if (cfg->player.move_down)
    {
        new_x -= cfg->dir_x * MOVE_SPEED;
        new_y -= cfg->dir_y * MOVE_SPEED;
    }
    if (cfg->player.move_left)
    {
        new_x += cfg->dir_y * MOVE_SPEED;
        new_y -= cfg->dir_x * MOVE_SPEED;
    }
    if (cfg->player.move_right)
    {
        new_x -= cfg->dir_y * MOVE_SPEED;
        new_y += cfg->dir_x * MOVE_SPEED;
    }
    
    // Collision detection
    if (!is_wall(cfg, new_x, cfg->player.y))
        cfg->player.x = new_x;
    if (!is_wall(cfg, cfg->player.x, new_y))
        cfg->player.y = new_y;
}

void handle_keys(mlx_key_data_t keydata, void *param)
{
    t_config *cfg = (t_config *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(cfg->mlx);
    
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W) cfg->player.move_up = 1;
        if (keydata.key == MLX_KEY_S) cfg->player.move_down = 1;
        if (keydata.key == MLX_KEY_A) cfg->player.move_left = 1;
        if (keydata.key == MLX_KEY_D) cfg->player.move_right = 1;
        if (keydata.key == MLX_KEY_LEFT) cfg->player.rotate_left = 1;
        if (keydata.key == MLX_KEY_RIGHT) cfg->player.rotate_right = 1;
    }

    if (keydata.action == MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_W) cfg->player.move_up = 0;
        if (keydata.key == MLX_KEY_S) cfg->player.move_down = 0;
        if (keydata.key == MLX_KEY_A) cfg->player.move_left = 0;
        if (keydata.key == MLX_KEY_D) cfg->player.move_right = 0;
        if (keydata.key == MLX_KEY_LEFT) cfg->player.rotate_left = 0;
        if (keydata.key == MLX_KEY_RIGHT) cfg->player.rotate_right = 0;
    }
}



void render_frame(void *param)
{
    t_config *cfg = (t_config *)param;
    
    // Clear screen
    memset(cfg->img->pixels, 0, cfg->img->width * cfg->img->height * sizeof(uint32_t));
    
    update_player_position(cfg);
    
    // Perform 3D raycasting (this now also stores ray data)
    // raycasting(cfg);
    
    // Draw 2D minimap with rays
    draw_map(cfg);           // Your existing 2D map drawing
    draw_player(cfg);        // Your existing player drawing
    draw_rays_on_minimap(cfg); // New: draw the rays!
}