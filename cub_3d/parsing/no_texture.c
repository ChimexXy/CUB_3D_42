/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:49:52 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/29 21:50:21 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_no(t_config *config, char *line, int r, bool *flag)
{
	if (line[r] == 'N' && line[r + 1] == 'O' && is_all_space(line[r + 2]))
	{
		if (*flag == 1)
			return (p_error("Config not valid\n"), 0);
		r += 2;
		skip_all_space(&r, line);
		if (!line[r])
			return (p_error("Config not valid\n"), 0);
		config->txt->no_texture = ft_strdup(line + r);
		if (!config->txt->no_texture)
			return (p_error(ERR_MEM), 0);
		*flag = 1;
		return (2);
	}
	return (1);
}

static int	check_rsl(t_config *config, t_var *var, t_file **file, t_file **tmp)
{
	static int	count;
	int			res;

	if (real_char_len((*tmp)->line) > 1)
		count++;
	res = check_no(config, (*tmp)->line, var->r, &var->flag);
	if (!res)
		return (0);
	else if (res == 2)
	{
		if (count > 4)
			return (p_error("Config not valid\n"), 0);
		*tmp = (*tmp)->next;
		free_node(file, var->n);
		var->n--;
		return (2);
	}
	return (1);
}

bool	no_texture(t_config *config, t_file **file)
{
	t_var	var;
	t_file	*tmp;

	var.flag = 0;
	var.n = -1;
	tmp = *file;
	while (tmp && ++var.n != -2)
	{
		var.r = 0;
		skip_all_space(&var.r, tmp->line);
		if (!tmp->line[var.r])
		{
			tmp = tmp->next;
			continue ;
		}
		var.ret = check_rsl(config, &var, file, &tmp);
		if (var.ret == 0)
			return (0);
		else if (var.ret == 2)
			continue ;
		tmp = tmp->next;
	}
	if (!var.flag)
		return (p_error("Config not valid\n"), 0);
	return (1);
}
