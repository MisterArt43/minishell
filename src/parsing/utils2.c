/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:00:38 by abucia            #+#    #+#             */
/*   Updated: 2022/09/30 14:00:38 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static int	ft_intlen(int n, int i)
{
	if (n <= -10)
		return (ft_intlen(-(n / 10), i + 2));
	if (n < 0)
		return (ft_intlen(-(n / 10), i + 1));
	if (n >= 10)
		return (ft_intlen(n / 10, i + 1));
	else
		return (i + 1);
}

void	add_numlen(int *n, int mode)
{
	int	ret;

	ret = 0;
	if (mode == 0)
	{
		ret = *n % 10 + '0';
		*n /= 10;
	}
	else
	{
		ret = -(n % 10) + '0';
		*n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n, t_global *g)
{
	int		numlen;
	char	*num;

	numlen = ft_intlen(n, 1);
	if (g != NULL)
		num = ft_gc_add_back(&g->gc_parsing, ft_gc_new(\
		malloc(numlen), "error malloc in itoa", g));
	else
		num = malloc(numlen);
	if (!num)
		return (NULL);
	*(num + numlen-- - 1) = '\0';
	if (n >= 0)
	{
		while (numlen--)
			*(num + numlen) = add_numlen(&n, 0);
		return (num);
	}
	*num = '-';
	while (--numlen)
		*(num + numlen) = add_numlen(&n, 1);
	return (num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	neg;

	i = 0;
	j = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != 0)
	{
		j *= 10;
		j += str[i] - '0';
		i++;
	}
	return (j * neg);
}
