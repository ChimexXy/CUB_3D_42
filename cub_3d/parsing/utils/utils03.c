/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:19:50 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/29 22:21:20 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	delete_just_sps_head(t_file **file)
{
	t_file	*tp1;

	while (*file && (just_all_space((*file)->line) || !(*file)->line[0]))
	{
		tp1 = *file;
		*file = (*file)->next;
		free(tp1->line);
		free(tp1);
	}
}

void	delete_just_sps_last(t_file *file)
{
	t_file	*tp1;
	t_file	*tp2;

	tp1 = file;
	while (tp1 && !just_all_space(tp1->line) && tp1->line[0])
	{
		tp2 = tp1;
		tp1 = tp1->next;
	}
	while (tp1 && (just_all_space(tp1->line) || !tp1->line[0]))
		tp1 = tp1->next;
	if (!tp1)
	{
		tp1 = tp2->next;
		tp2->next = NULL;
		while (tp1)
		{
			tp2 = tp1->next;
			free(tp1->line);
			free(tp1);
			tp1 = tp2;
		}
	}
}

bool	just_all_space(char *line)
{
	int		r;

	r = 0;
	if (!line[r])
		return (0);
	while (line[r])
	{
		if (!is_all_space(line[r]))
			return (0);
		r++;
	}
	return (1);
}

void	skip_all_space(int *r, char *str)
{
	while ((str[*r] >= 8 && str[*r] <= 13) || str[*r] == 32)
		*r = *r + 1;
}

bool	is_all_space(char c)
{
	return ((c >= 8 && c <= 13) || c == 32);
}
