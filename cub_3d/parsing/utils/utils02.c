/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:19:40 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/29 22:19:41 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	real_char_len(char *str)
{
	int		r;
	int		len;

	len = 0;
	r = -1;
	while (str[++r])
	{
		if (is_all_space(str[r]))
			continue ;
		len++;
	}
	return (len);
}

void	free_node(t_file **file, int n)
{
	t_file	*tp1;
	t_file	*tp2;
	int		r;

	r = -1;
	tp1 = *file;
	if (!n)
		*file = (*file)->next;
	else
	{
		while (++r < n - 1)
			tp1 = tp1->next;
		tp2 = tp1;
		tp1 = tp2->next;
		tp2->next = tp1->next;
	}
	free(tp1->line);
	free(tp1);
}

int	number_of_words(char **split)
{
	int		r;

	r = 0;
	while (split[r])
		r++;
	if (r != 3)
		p_error("Config not valid\n");
	return (r);
}

bool	is_correct_rgb(int n)
{
	return (n >= 0 && n <= 255);
}

bool	just_space(char *line)
{
	int		r;

	r = 0;
	if (!line[r])
		return (0);
	while (line[r])
	{
		if (!is_space(line[r]))
			return (0);
		r++;
	}
	return (1);
}
