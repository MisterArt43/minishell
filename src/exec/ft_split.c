/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:44:37 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/02 20:13:23 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static int	ft_lensplit(char const *str, char c, int *start)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] == c && str[i])
		i++;
	if (str[i] && str[i] != c)
		res++;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (str[i] != 0)
				res++;
		}
		else
			i++;
	}
	while (str[*start] == c && str[*start])
		*start += 1;
	return (res);
}

static int	ft_end(char const *str, char c, int start)
{
	int		end;

	end = start;
	while (str[end] && str[end] != c)
		end++;
	return (end);
}

static char	*ft_fill(char const *str, char c, char *res, int *start)
{
	int		i;

	i = 0;
	while (ft_end(str, c, *start) != *start)
	{
		res[i] = str[*start];
		*start += 1;
		i++;
	}
	res[i] = '\0';
	while (str[*start] == c && str[*start])
		*start += 1;
	return (res);
}

static char	**ft_free(char **res, int i)
{
	while (i != 0)
		free(res[i--]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *str, char c, t_global *g)
{
	char	**res;
	int		start;
	int		i;

	start = 0;
	i = 0;
	res = ft_gc_add_back(&g->gc_parsing, ft_gc_new(malloc((1 + ft_lensplit(\
	str, c, &start)) * (sizeof(char *))), "malloc error in ft_split", g));
	while (str[start])
	{
		res[i] = ft_gc_add_back(&g->gc_parsing, ft_gc_new(\
		malloc((1 + ft_end(str, c, start) - start) * sizeof(char)), \
		"malloc error in ft_split", g));
		res[i] = ft_fill(str, c, res[i], &start);
		i++;
	}
	res[i] = NULL;
	return (res);
}
