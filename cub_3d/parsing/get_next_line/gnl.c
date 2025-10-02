/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:15:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/26 15:58:55 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static void	g_read_line(char **tmp, char **store, int fd)
{
	t_vr	lstv;

	while (1)
	{
		lstv.buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!lstv.buffer)
			return ;
		lstv.byt = read(fd, lstv.buffer, BUFFER_SIZE);
		if (lstv.byt <= 0)
		{
			if (!lstv.byt)
				g_free_l(&lstv.buffer, 0, 0);
			else
				g_free_l(&lstv.buffer, 0, store);
			return ;
		}
		lstv.buffer[lstv.byt] = '\0';
		*tmp = g_strjoin(*store, NULL);
		g_free_l(store, NULL, NULL);
		*store = g_strjoin(*tmp, lstv.buffer);
		g_free_l(tmp, &lstv.buffer, NULL);
		if (ft_strchr(*store, '\n'))
			return ;
	}
}

static char	*g_af_nln(char *str)
{
	char	*ma;
	size_t	a;
	size_t	b;

	if (!str)
		return (NULL);
	a = g_strlen(str);
	b = 0;
	while (str[b] && str[b] != '\n')
		b++;
	if (str[b] == '\n')
		b++;
	ma = (char *)malloc(sizeof(char) * (a - b + 1));
	if (!ma)
		return (NULL);
	a = 0;
	while (str[b])
	{
		ma[a] = str[b];
		a++;
		b++;
	}
	ma[a] = '\0';
	return (ma);
}

static char	*g_bf_nln(char *str)
{
	char	*ma;
	size_t	b;
	size_t	i;

	if (!str)
		return (NULL);
	b = 0;
	i = 0;
	while (str[b] && str[b] != '\n')
		b++;
	if (str[b] == '\n')
		b++;
	ma = (char *)malloc(sizeof(char) * (b + 1));
	if (!ma)
		return (NULL);
	while (i < b)
	{
		ma[i] = str[i];
		i++;
	}
	ma[i] = '\0';
	return (ma);
}

static char	*g_check_line(char **store, char **tmp)
{
	char	*oln;

	*tmp = g_strjoin(*store, NULL);
	g_free_l(store, NULL, NULL);
	*store = g_af_nln(*tmp);
	oln = g_bf_nln(*tmp);
	g_free_l(tmp, NULL, NULL);
	if (!**store)
		g_free_l(store, NULL, NULL);
	return (oln);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*tmp;
	char		*oln;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = NULL;
	oln = NULL;
	g_read_line(&tmp, &store, fd);
	if (store && *store)
		oln = g_check_line(&store, &tmp);
	if (!oln)
	{
		g_free_l(&store, NULL, NULL);
		return (NULL);
	}
	return (oln);
}
