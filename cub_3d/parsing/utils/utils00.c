/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:57:30 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/27 17:46:43 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	open_fd(char *file, int fd)
{
	if (fd != -1)
	{
		close(fd);
		fd = -1;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Problem in Opening file\n");
		exit(1);
	}
	return (fd);
}

void	p_error(const char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
}
