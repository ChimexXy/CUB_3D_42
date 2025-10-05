#include "raycasting.h"

void	draw_vertical_line(t_config *cfg, int x, int start, int end, uint32_t color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
			mlx_put_pixel(cfg->img, x, y, color);
		y++;
	}
}

static void	init_ray_direction(t_config *cfg, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = cfg->dir_x + cfg->plane_x * camera_x;
	ray->dir_y = cfg->dir_y + cfg->plane_y * camera_x;
	ray->map_x = (int)cfg->player.x;
	ray->map_y = (int)cfg->player.y;
}

static void	init_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	init_step_x(t_config *cfg, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cfg->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cfg->player.x)
			* ray->delta_dist_x;
	}
}

static void	init_step_y(t_config *cfg, t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cfg->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cfg->player.y)
			* ray->delta_dist_y;
	}
}

static int	check_hit(t_config *cfg, t_ray *ray)
{
	if (ray->map_y < 0 || ray->map_x < 0)
		return (1);
	if (!cfg->map[ray->map_y] || !cfg->map[ray->map_y][ray->map_x])
		return (1);
	if (cfg->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static void	perform_dda(t_config *cfg, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		hit = check_hit(cfg, ray);
	}
}

static double	calc_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		return (ray->side_dist_x - ray->delta_dist_x);
	else
		return (ray->side_dist_y - ray->delta_dist_y);
}

static void	calc_draw_bounds(double wall_dist, int *start, int *end)
{
	int	line_height;

	line_height = (int)(WIN_H / wall_dist);
	*start = -line_height / 2 + WIN_H / 2;
	if (*start < 0)
		*start = 0;
	*end = line_height / 2 + WIN_H / 2;
	if (*end >= WIN_H)
		*end = WIN_H - 1;
}

static uint32_t	get_wall_color(int side)
{
	if (side == 1)
		return (0x888888FF);
	else
		return (0xCCCCCCFF);
}

static void	cast_single_ray(t_config *cfg, int x)
{
	t_ray		ray;
	double		wall_dist;
	int			draw_start;
	int			draw_end;
	uint32_t	color;

	init_ray_direction(cfg, x, &ray);
	init_delta_dist(&ray);
	init_step_x(cfg, &ray);
	init_step_y(cfg, &ray);
	perform_dda(cfg, &ray);
	wall_dist = calc_wall_dist(&ray);
	calc_draw_bounds(wall_dist, &draw_start, &draw_end);
	color = get_wall_color(ray.side);
	draw_vertical_line(cfg, x, draw_start, draw_end, color);
}

void	raycasting(t_config *cfg)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(cfg, x);
		x++;
	}
}

static int	check_point_wall(t_config *cfg, int mx, int my)
{
	if (my < 0 || mx < 0)
		return (1);
	if (!cfg->map[my] || !cfg->map[my][mx])
		return (1);
	if (cfg->map[my][mx] == '1')
		return (1);
	return (0);
}

int	is_wall(t_config *cfg, double x, double y)
{
	double	m;
	int		i;
	int		mx;
	int		my;

	m = (1.0 / 6.0) * 0.5;
	i = 0;
	while (i < 4)
	{
		if (i == 0)
			mx = (int)(x - m);
		else if (i == 1)
			mx = (int)(x + m);
		else if (i == 2)
			mx = (int)(x - m);
		else
			mx = (int)(x + m);
		if (i < 2)
			my = (int)(y - m);
		else
			my = (int)(y + m);
		if (check_point_wall(cfg, mx, my))
			return (1);
		i++;
	}
	return (0);
}

static void	rotate(t_config *cfg, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cfg->dir_x;
	cfg->dir_x = cfg->dir_x * cos(angle) - cfg->dir_y * sin(angle);
	cfg->dir_y = old_dir_x * sin(angle) + cfg->dir_y * cos(angle);
	old_plane_x = cfg->plane_x;
	cfg->plane_x = cfg->plane_x * cos(angle) - cfg->plane_y * sin(angle);
	cfg->plane_y = old_plane_x * sin(angle) + cfg->plane_y * cos(angle);
}

static void	apply_rotation(t_config *cfg)
{
	if (cfg->player.rotate_right)
		rotate(cfg, ROT_SPEED);
	if (cfg->player.rotate_left)
		rotate(cfg, -ROT_SPEED);
}

static void	apply_movement(t_config *cfg, double *nx, double *ny)
{
	if (cfg->player.move_up)
	{
		*nx += cfg->dir_x * MOVE_SPEED;
		*ny += cfg->dir_y * MOVE_SPEED;
	}
	if (cfg->player.move_down)
	{
		*nx -= cfg->dir_x * MOVE_SPEED;
		*ny -= cfg->dir_y * MOVE_SPEED;
	}
	if (cfg->player.move_left)
	{
		*nx += cfg->dir_y * MOVE_SPEED;
		*ny -= cfg->dir_x * MOVE_SPEED;
	}
	if (cfg->player.move_right)
	{
		*nx -= cfg->dir_y * MOVE_SPEED;
		*ny += cfg->dir_x * MOVE_SPEED;
	}
}

void	update_player_position(t_config *cfg)
{
	double	nx;
	double	ny;

	nx = cfg->player.x;
	ny = cfg->player.y;
	apply_rotation(cfg);
	apply_movement(cfg, &nx, &ny);
	if (!is_wall(cfg, nx, cfg->player.y))
		cfg->player.x = nx;
	if (!is_wall(cfg, cfg->player.x, ny))
		cfg->player.y = ny;
}

static void	set_key_state(mlx_key_data_t key, t_config *cfg, int press)
{
	if (key.key == MLX_KEY_W)
		cfg->player.move_up = press;
	if (key.key == MLX_KEY_S)
		cfg->player.move_down = press;
	if (key.key == MLX_KEY_A)
		cfg->player.move_left = press;
	if (key.key == MLX_KEY_D)
		cfg->player.move_right = press;
	if (key.key == MLX_KEY_LEFT)
		cfg->player.rotate_left = press;
	if (key.key == MLX_KEY_RIGHT)
		cfg->player.rotate_right = press;
}

void	handle_keys(mlx_key_data_t key, void *param)
{
	t_config	*cfg;
	int			press;

	cfg = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(cfg->mlx);
	press = (key.action == MLX_PRESS || key.action == MLX_REPEAT);
	if (key.action == MLX_RELEASE)
		press = 0;
	set_key_state(key, cfg, press);
}

void	render_frame(void *param)
{
	t_config	*cfg;

	cfg = (t_config *)param;
	memset(cfg->img->pixels, 0,
		cfg->img->width * cfg->img->height * sizeof(uint32_t));
	update_player_position(cfg);
	raycasting(cfg);
}