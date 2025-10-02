/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:48:28 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:19:48 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_file	*linked_list(int ln)
{
	t_file	*head;
	t_file	*tmp;
	t_file	*curr;

	head = malloc(sizeof(t_file));
	if (!head)
		return (p_error(ERR_MEM), exit (1), NULL);
	tmp = head;
	tmp->next = NULL;
	curr = NULL;
	while (--ln)
	{
		curr = malloc(sizeof(t_file));
		if (!curr)
			return (p_error(ERR_MEM), t_file_free(head), exit (1), NULL);
		curr->next = NULL;
		curr->line = NULL;
		tmp->next = curr;
		tmp = curr;
	}
	return (head);
}
