/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:01:24 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:42:04 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	cline_map(int fd)
{
	char	*gnl;
	int		ln;

	ln = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		ln++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (ln);
}

static void	delete_newline(t_file *file)
{
	char	*tmp;
	char	*lks;
	int		v;

	while (file)
	{
		tmp = file->line;
		lks = file->line;
		file->line = malloc(ft_strlen(tmp));
		if (!file->line)
			p_error(ERR_MEM);
		v = 0;
		while (*tmp)
		{
			if (*tmp != '\n')
				file->line[v++] = *tmp;
			tmp++;
		}
		file->line[v] = '\0';
		free(lks);
		file = file->next;
	}
}

static void	populate_map(t_file *file, int fd, int ln)
{
	int		r;

	r = -1;
	while (++r < ln)
	{
		file->line = get_next_line(fd);
		file = file->next;
	}
}

bool	is_valid_map(t_config *config, char *pmap)
{
	t_file	*file;
	t_file	*tmp;
	int		fd;
	int		ln;

	fd = open_fd(pmap, -1);
	ln = cline_map(fd);
	if (!ln)
		return (p_error("Map not valid\n"), 0);
	file = linked_list(ln);
	fd = open_fd(pmap, fd);
	populate_map(file, fd, ln);
	delete_newline(file);
	tmp = file;
	if (!is_valid_config(config, &file))
		return (free(config->txt), 0);
	delete_just_sps_head(&file);
	delete_just_sps_last(file);
	tmp = file;
	if (!_map(config, file, pmap, &ln))
		return (free_all(config, file), 0);
	return (1);
}
