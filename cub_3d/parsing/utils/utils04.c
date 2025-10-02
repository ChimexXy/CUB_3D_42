/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:12:55 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:43:23 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	p1char(char **ptr)
{
	if (!*ptr || !ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	p2char(char ***ptr)
{
	int	r;

	if (!ptr || !*ptr)
		return ;
	r = 0;
	while ((*ptr)[r])
		free((*ptr)[r++]);
	free(*ptr);
	*ptr = NULL;
}

void	free_rgb(t_rgb *rgb)
{
	free(rgb);
	rgb = NULL;
}

void	t_file_free(t_file *file)
{
	t_file	*l1;

	while (file)
	{
		p1char(&file->line);
		l1 = file;
		file = file->next;
		free(l1);
	}
}

void	free_all(t_config *config, t_file *file)
{
	t_file_free(file);
	free_rgb(config->floor_color);
	free_rgb(config->ceiling_color);
	p1char(&config->txt->no_texture);
	p1char(&config->txt->so_texture);
	p1char(&config->txt->we_texture);
	p1char(&config->txt->ea_texture);
	free(config->txt);
	p2char(&config->map);
}
