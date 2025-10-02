/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:06:02 by mbarhoun          #+#    #+#             */
/*   Updated: 2024/11/01 21:35:17 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ma;
	size_t	mlen;
	size_t	b;

	if (!s)
		return (NULL);
	mlen = ft_strlen(s);
	b = 0;
	if (start >= (unsigned int)mlen)
		return (ft_strdup(""));
	if (len > mlen - start)
		len = mlen - start;
	ma = (char *)malloc(sizeof(char) * (len + 1));
	if (!ma)
		return (NULL);
	while (b < len)
	{
		ma[b] = s[start + b];
		b++;
	}
	ma[b] = '\0';
	return (ma);
}
