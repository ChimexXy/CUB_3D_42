/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:33:00 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/27 22:14:02 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	has_player(int *player, int *r)
{
	if (*player)
		return (p_error("Map not valid\n"), 0);
	*r = *r + 1;
	*player = 1;
	return (1);
}

static bool	check_content_mp(char *map, int *r, int *player)
{
	while (map[*r])
	{
		skip_space(r, map);
		if (!map[*r])
			break ;
		if (is_player(map[*r]))
		{
			if (!has_player(player, r))
				return (0);
			continue ;
		}
		if (!is_normal(map[*r]))
			return (p_error("Map not valid\n"), 0);
		*r = *r + 1;
	}
	return (1);
}

bool	first_line_mp(t_config *config, int p_block, int r)
{
	while (config->map[p_block][r])
	{
		skip_space(&r, config->map[p_block]);
		if (!config->map[p_block][r])
			return (1);
		if (config->map[p_block][r] != '1')
			return (p_error("Map not valid\n"), 0);
		r++;
	}
	return (1);
}

bool	check_map_walls(t_config *config, int *p_block, int ln, int player)
{
	int		r;

	while (ln--)
	{
		r = 0;
		skip_space(&r, config->map[*p_block]);
		if (config->map[*p_block][r++] != '1')
			return (p_error("Map not valid\n"), 0);
		if (!check_content_mp(config->map[*p_block], &r, &player))
			return (0);
		r--;
		if (is_space(config->map[*p_block][r]))
			back_space(&r, config->map[*p_block]);
		if (config->map[*p_block][r] != '1')
			return (p_error("Map not valid\n"), 0);
		*p_block = *p_block + 1;
	}
	if (!player)
		return (p_error("Map not valid\n"), 0);
	return (1);
}

bool	last_line_mp(t_config *config, int p_block, int r)
{
	while (config->map[p_block][r])
	{
		skip_space(&r, config->map[p_block]);
		if (!config->map[p_block][r])
			return (1);
		if (config->map[p_block][r] != '1')
			return (p_error("Map not valid\n"), 0);
		r++;
	}
	return (1);
}
