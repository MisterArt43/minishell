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
	res = ft_gc_add_back(&g->gc_parsing, ft_gc_new(malloc((len + 1) * sizeof(char)), "invalid malloc in strjoin", g));
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

int	ft_nstrncmp(const char *s1, const char *s2, size_t n, size_t i)
{
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

void	ft_putendl_fd(char	*s, int fd)
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
	write(fd, "\n", 1);
}
