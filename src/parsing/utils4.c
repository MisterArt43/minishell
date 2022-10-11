/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:51:15 by tschlege          #+#    #+#             */
/*   Updated: 2022/10/11 18:53:07 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
