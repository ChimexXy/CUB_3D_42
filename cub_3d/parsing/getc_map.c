/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getc_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:52:26 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/29 21:52:51 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**load_map_content(int ln, t_file *file)
{
	char	**map;
	int		r;

	r = 0;
	if (ln < 3)
		return (p_error("Map not valid\n"), NULL);
	map = (char **)malloc(sizeof(char *) * (ln + 1));
	if (!map)
		return (p_error(ERR_MEM), NULL);
	while (r < ln)
	{
		map[r] = ft_strdup(file->line);
		if (!map[r])
			return (p_error(ERR_MEM), NULL);
		file = file->next;
		r++;
	}
	map[r] = NULL;
	return (map);
}

char	**get_content_map(t_file *file, int *ln)
{
	t_file	*tp1;

	tp1 = file;
	*ln = 0;
	while (tp1)
	{
		*ln = *ln + 1;
		tp1 = tp1->next;
	}
	return (load_map_content(*ln, file));
}
