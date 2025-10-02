/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:02 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/09/30 18:06:05 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkovf(long long ma, int mg, char c)
{
	if ((ma >= 922337203685477580 && mg == 1 && c >= '7') 
		|| (ma >= 922337203685477580 && mg == -1 && c >= '8'))
		return (0);
	return (1);
}

static int	ft_check(char *str)
{
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			str++;
		else if (*str != ',')
			return (1337);
	}
	return (1);
}

int	ft_atoi(char *str)
{
	size_t	ma;
	int		mg;

	ma = 0;
	mg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			mg = -1;
	while (*str >= 48 && *str <= 57)
	{
		if (!ft_checkovf(ma, mg, *str))
		{
			if (mg == 1)
				return (-1);
			if (mg == -1)
				return (0);
		}
		ma = (ma * 10) + (*str++ - 48);
	}
	if (ft_check(str) == 1337)
		return (1337);
	return (ma * mg);
}
