/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 04:28:26 by abucia            #+#    #+#             */
/*   Updated: 2022/09/08 04:28:26 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1, t_global *g)
{
	char	*cpy;
	size_t	i;

	i = 0;
	if (g->gc_parsing != NULL)
		cpy = (char *)ft_gc_add_back(&g->gc_parsing, ft_gc_new(malloc((ft_strlen(s1) + 1) * \
	sizeof(char)), "An error occur while mallocing", g));
	else
		cpy = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_global *g)
{
	size_t		i;
	char		*res;

	i = 0;
	if (start > ft_strlen(s) + 1)
		return (ft_strdup("", g));
	while (s[start + i] && i != len)
		i++;
	if (&g->gc_parsing != NULL)
	{
		res = (char *)ft_gc_add_back(&g->gc_parsing, ft_gc_new(malloc((i + 1) * sizeof(char)), \
		"An error occur while mallocing", g));
	}
	else
		res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (len != 0 && s[start])
	{
		res[i++] = s[start++];
		len--;
	}
	res[i] = 0;
	return (res);
}
