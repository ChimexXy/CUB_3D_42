/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:58:09 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:42:43 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_valid_config(t_config *config, t_file **file)
{
	if (!floor_color(config, file))
		return (0);
	if (!ceiling_color(config, file))
		return (free_rgb(config->floor_color), 0);
	config->txt = malloc(sizeof(t_textures));
	if (!config->txt)
		return (p_error(ERR_MEM), free_rgb(config->floor_color), 
			free_rgb(config->ceiling_color), 0);
	if (!no_texture(config, file))
		return (free_rgb(config->floor_color), free_rgb(config->ceiling_color), 
			0);
	if (!so_texture(config, file))
		return (free_rgb(config->floor_color), free_rgb(config->ceiling_color), 
			p1char(&config->txt->no_texture), 0);
	if (!we_texture(config, file))
		return (free_rgb(config->floor_color), free_rgb(config->ceiling_color), 
			p1char(&config->txt->no_texture), p1char(&config->txt->so_texture), 
			0);
	if (!ea_texture(config, file))
		return (free_rgb(config->floor_color), free_rgb(config->ceiling_color), 
			p1char(&config->txt->no_texture), p1char(&config->txt->so_texture), 
			p1char(&config->txt->we_texture), 0);
	return (1);
}
