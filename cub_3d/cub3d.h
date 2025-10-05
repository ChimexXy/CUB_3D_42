/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:18:06 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/29 21:41:36 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./parsing/parsing.h"
# include "./mlx/include/MLX42/MLX42.h"

# define ERR_MEM "Allocation Faield\n"

typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_textures
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}	t_textures;

typedef struct s_player {
    double x;   // position X in map (floating point!)
    double y;   // position Y in map (floating point!)
    int move_up;
    int move_down;
    int move_left;
    int move_right;
	int rotate_left;
	int rotate_right;
} t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;


   


typedef struct s_config
{
	char		**map;
	t_textures	*txt;
	t_rgb		*floor_color;
	t_rgb		*ceiling_color;
	int			pos_x;
	int			pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	////////////////// raycast
	mlx_t       *mlx;        // MLX42 instance
    mlx_image_t *img;   
	t_player player;
	t_ray *rays;  // Array to store ray data for visualization
    int num_rays;

}	t_config;

#endif