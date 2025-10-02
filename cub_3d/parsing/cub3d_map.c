/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:38:58 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:36:56 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	check_map_content(t_config *config, int ln)
{
	int	p_block;

	p_block = 1;
	if (!first_line_mp(config, 0, 0))
		return (0);
	if (!check_map_walls(config, &p_block, ln - 2, 0))
		return (0);
	if (!last_line_mp(config, p_block, 0))
		return (0);
	return (1);
}

bool	_map(t_config *config, t_file *file, char *pmap, int *ln)
{
	config->map = NULL;
	config->map = get_content_map(file, ln);
	if (!config->map)
		return (0);
	if (!check_map_content(config, *ln))
		return (0);
	if (!void_place(config->map))
		return (p_error("Map not valid\n"), 0);
	write_config(pmap);
	return (1);
}
