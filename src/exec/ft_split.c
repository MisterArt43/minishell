/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wati-Theo <wati-theo@protonmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:44:37 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/28 00:44:37 by Wati-Theo        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*retturn;

	retturn = b;
	while (len)
	{
		len--;
		*((unsigned char *)b + len) = (unsigned char)c;
	}
	return (retturn);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*retturn;

	retturn = malloc(count * size);
	if (!retturn)
		return (NULL);
	return (ft_memset(retturn, '\0', count * size));
}

char	*ft_substrw(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*the_nouvelle;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (start > s_len)
		return (ft_calloc(1, sizeof(char)));
	if ((s_len - start) > len)
		the_nouvelle = ft_calloc((len + 1), sizeof(char));
	else
	{
		the_nouvelle = ft_calloc((s_len - start + 1), sizeof(char));
		len = s_len - start + 1;
	}
	if (!the_nouvelle)
		return (NULL);
	while (s[start + i] && i < len)
	{
		the_nouvelle[i] = s[start + i];
		i++;
	}
	return (the_nouvelle);
}

char	**ft_freebox(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static	size_t	ft_word_count(char const *s, char c)
{
	int		i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] == (unsigned char)c)
			i++;
		while (s[i] && s[i] != (unsigned char)c)
			i++;
		if (!s[i] && s[i - 1] != (unsigned char)c)
			wc++;
		wc++;
	}
	return (wc);
}

static	int	ft_word_len(char const *s, char c, int *start)
{
	size_t	word_len;

	word_len = 0;
	while (s[*start] == (unsigned char)c)
		*start = *start + 1;
	while (s[*start] && s[*start] != (unsigned char)c)
	{
		*start = *start + 1;
		word_len++;
	}
	if (s[*start] == (unsigned char)c || !s[*start])
		return (word_len);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**str;
	int		start;
	size_t	word_len;
	size_t	i;

	if (!s)
		return (NULL);
	wc = ft_word_count(s, c);
	if (!wc)
		return (ft_calloc(1, sizeof(char *)));
	str = ft_calloc(wc, sizeof(char *));
	if (!str)
		return (NULL);
	start = 0;
	i = 0;
	while (i + 1 < wc)
	{
		word_len = ft_word_len(s, c, &start);
		str[i] = ft_substrw(s, start - word_len, word_len);
		if (!str[i++])
			return (ft_freebox(str));
	}
	str[i] = 0;
	return (str);
}