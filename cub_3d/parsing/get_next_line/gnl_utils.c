/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:08:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/06/26 16:03:55 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

size_t	g_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*g_strdup(const char *s1)
{
	char	*ma;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	ma = (char *)malloc(g_strlen(s1) + 1);
	if (!ma)
		return (NULL);
	while (s1[i])
	{
		ma[i] = s1[i];
		i++;
	}
	ma[i] = '\0';
	return (ma);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
		if (*s++ == (char)c)
			return ((char *)--s);
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*g_strjoin(char const *s1, char const *s2)
{
	t_vr	lstv;
	char	*ma;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (g_strdup(s2));
	if (!s2)
		return (g_strdup(s1));
	lstv.mlen1 = g_strlen(s1);
	lstv.mlen2 = g_strlen(s2);
	lstv.i = 0;
	lstv.a = 0;
	ma = (char *)malloc(sizeof(char) * (lstv.mlen1 + lstv.mlen2 + 1));
	if (!ma)
		return (NULL);
	while (s1[lstv.i])
	{
		ma[lstv.i] = s1[lstv.i];
		lstv.i++;
	}
	while (s2[lstv.a])
		ma[lstv.i++] = s2[lstv.a++];
	ma[lstv.i] = '\0';
	return (ma);
}

void	g_free_l(char **s1, char **s2, char **s3)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}
