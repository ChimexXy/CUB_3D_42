/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:30:36 by mbarhoun          #+#    #+#             */
/*   Updated: 2024/11/03 22:08:05 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cword(char const *s, char c)
{
	size_t	b;
	size_t	ct;

	b = 1;
	ct = 0;
	while (*s)
	{
		if (*s != c && b == 1)
		{
			b = 0;
			ct++;
		}
		if (*s == c)
			b = 1;
		s++;
	}
	return (ct);
}

static size_t	ft_nlen(char const *s, char c)
{
	size_t	b;

	b = 0;
	while (*s && *s != c)
	{
		b++;
		s++;
	}
	return (b);
}

static void	ft_free(char **ma)
{
	size_t	b;

	b = 0;
	while (ma[b])
	{
		free(ma[b]);
		b++;
	}
	free(ma);
}

static char	**ft_spl(char const *s1, char **ma, char c)
{
	size_t	b;
	size_t	sb;

	b = 0;
	sb = 0;
	while (s1[b])
	{
		while (s1[b] == c)
			b++;
		if (s1[b])
		{
			ma[sb] = ft_substr(s1, b, ft_nlen(s1 + b, c));
			if (!ma[sb])
			{
				ft_free(ma);
				return (NULL);
			}
			sb++;
		}
		while (s1[b] && s1[b] != c)
			b++;
	}
	ma[sb] = NULL;
	return (ma);
}

char	**ft_split(char const *s1, char c)
{
	size_t	cword;
	char	**ma;

	if (!s1)
		return (NULL);
	cword = ft_cword(s1, c);
	ma = (char **)malloc(sizeof(char *) * (cword + 1));
	if (!ma)
		return (NULL);
	return (ft_spl(s1, ma, c));
}
