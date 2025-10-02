/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:48:26 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/27 21:59:50 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	skip_space(int *r, char *str)
{
	while (str[*r] == 32)
		*r = *r + 1;
}

void	back_space(int *r, char *str)
{
	while (*r > 0 && str[*r] == 32)
		*r = *r - 1;
}

bool	is_player(char c)
{
	return (c == 'W' || c == 'E' || c == 'N' || c == 'S');
}

bool	is_space(char c)
{
	return (c == 32);
}

bool	is_normal(char c)
{
	return (c == '1' || c == '0' || c == ' ');
}
