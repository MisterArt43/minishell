/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 04:28:26 by abucia            #+#    #+#             */
/*   Updated: 2022/10/01 21:32:50 by abucia           ###   ########lyon.fr   */
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
	if (g != NULL)
		cpy = (char *)ft_gc_add_back(&g->gc_parsing, ft_gc_new(\
		malloc((ft_strlen(s1) + 1) * sizeof(char)), \
		"An error occur while mallocing", g));
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
	if (g != NULL)
	{
		res = (char *)ft_gc_add_back(&g->gc_parsing, ft_gc_new(malloc(\
		(i + 1) * sizeof(char)), "An error occur while mallocing", g));
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	if (!s1)
		return (-1);
	if (!n)
		return (0);
	while ((s1[i] == s2[i]) && i < (n - 1) && s1[i] && s2[i])
		i++;
	if (s1[i] != s2[i])
		res = ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (res);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= dst_len)
		return (dstsize + ft_strlen(src));
	while (i < (dstsize - dst_len - 1) && i < dstsize && i < src_len)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (ft_strlen(src) + dst_len);
}
