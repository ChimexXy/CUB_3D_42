/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:17:52 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:02:48 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	main(int ac, char **av)
{
	t_config	config;

	if (ac != 2 || !handle_format(av[1], ".cub"))
		return (p_error("Argument not valid\n"), 0);
	if (is_valid_map(&config, av[1]))
		return (1);
	return (0);
}
