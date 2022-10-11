/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:48:51 by tschlege          #+#    #+#             */
/*   Updated: 2022/10/11 18:55:08 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*ft_strjoin2(char *s1, char *s2, char *res, t_dual_int i)
{
	if (!res)
		return (NULL);
	while (s1[i.a])
	{
		res[i.a] = s1[i.a];
		i.a++;
	}
	i.b = 0;
	while (s2[i.b])
	{
		res[i.a] = s2[i.b];
		i.a++;
		i.b++;
	}
	res[i.a] = 0;
	return (res);
}

char	*ft_strjoin(char *s1, char *s2, t_global *g)
{
	char		*res;
	t_dual_int	i;

	if (!s1)
	{
		if (!s2)
			return (NULL);
		else
			return (s2);
	}
	if (!s2)
		return (s1);
	i.a = 0;
	i.b = ft_strlen(s1) + ft_strlen(s2);
	if (g != NULL)
	{
		res = ft_gc_add_back(&g->gc_parsing, ft_gc_new(\
		malloc((i.b + 1) * sizeof(char)), "invalid malloc in strjoin", g));
	}
	else
		res = malloc((i.b + 1) * sizeof(char));
	return (ft_strjoin2(s1, s2, res, i));
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

void	ft_putstr_fd(char	*s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &(s[i]), 1);
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
