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

size_t	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
	if (g != NULL && g->gc_parsing != NULL)
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
	if (g != NULL && &g->gc_parsing != NULL)
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

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || ((c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z')))
		return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, t_global *g)
{
	char	*res;
	int		i;
	int		len;

	if (!s1)
	{
		if (!s2)
			return (NULL);
		else
			return (s2);
	}
	if (!s2)
		return (s1);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (g != NULL && &g->gc_parsing != NULL)
	{
		res = ft_gc_add_back(&g->gc_parsing, ft_gc_new(\
		malloc((len + 1) * sizeof(char)), "invalid malloc in strjoin", g));
	}
	else
		res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	len = 0;
	while (s2[len])
	{
		res[i] = s2[len];
		i++;
		len++;
	}
	res[i] = 0;
	return (res);
}

int	ft_nstrncmp(const char *s1, const char *s2, size_t n, size_t start)
{
	if (ft_strlen(s1) < start || ft_strlen(s2) < start)
		return (1);
	while (s1[start] != '\0' && s2[start] != '\0' && start < n)
	{
		if ((unsigned char)s1[start] != (unsigned char)s2[start])
			return ((unsigned char)s1[start] - (unsigned char)s2[start]);
		start++;
	}
	if (start == n)
		return (0);
	return ((unsigned char)s1[start] - (unsigned char)s2[start]);
}
