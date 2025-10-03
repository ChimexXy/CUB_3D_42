/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_void.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:51:17 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/10/02 15:34:56 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	is_correct_void(char **map, int y, int x)
{
	if (map[y][x] == '0' || is_player(map[y][x]))
	{
		if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
			|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
			return (0);
		if (x > ft_strlen(map[y + 1]) || x > ft_strlen(map[y - 1]))
			return (0);
	}
	return (1);
}

bool	void_place(char **map)
{
	int		all_y;
	int		y;
	int		x;

	all_y = 0;
	y = 0;
	while (map[all_y])
		all_y++;
	while (y < all_y)
	{
		x = 0;
		while (x < ft_strlen(map[y]))
		{
			if (!is_correct_void(map, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
