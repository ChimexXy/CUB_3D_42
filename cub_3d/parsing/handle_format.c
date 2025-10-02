/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:51:57 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/29 21:51:58 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	handle_format(char *path, char *format)
{
	int		r;

	r = ft_strlen(path) - 4;
	if (!ft_strcmp(path + r, format))
		return (1);
	return (0);
}
