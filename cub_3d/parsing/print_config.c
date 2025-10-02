/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:53:36 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/27 17:47:58 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	write_config(char *pmap)
{
	int		fd;
	int		r;
	char	*gnl;

	fd = open_fd(pmap, -1);
	r = 0;
	while (r < 6)
	{
		gnl = get_next_line(fd);
		if (!just_all_space(gnl))
		{
			printf("%s", gnl);
			r++;
		}
		free(gnl);
	}
	close(fd);
}
