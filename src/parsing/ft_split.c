/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:39:49 by abucia            #+#    #+#             */
/*   Updated: 2022/09/14 17:01:40 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	skip_to_next_word(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == ' ' \
		|| str[*i] == '\t' \
		|| str[*i] == '\n' \
		|| str[*i] == '\r')
			*i += 1;
		else
			return ;
	}
}

void	skip_quote(char *str, int *i)
{
	char	c;

	c = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != c)
		*i += 1;
	if (str[*i] == c)
		*i += 1;
}

void	skip_word(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == ' ' \
		|| str[*i] == '\t' \
		|| str[*i] == '\n' \
		|| str[*i] == '\r' \
		|| str[*i] == '\"' \
		|| str[*i] == '\'')
			return ;
		*i += 1;
	}
}

void	sort_split(t_lst_cmd **cmd, int *i, t_global *g, int start)
{
	skip_to_next_word((*cmd)->command, i);
	if ((*cmd)->command[*i] == '\'' || (*cmd)->command[*i] == '\"')
	{
		start = *i;
		skip_quote((*cmd)->command, i);
		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, ft_substr((*cmd)->command, start, *i, g), g));
		printf("Quote\n");
	}
	else if ((*cmd)->command[*i] == 0)
		return ;
	else
	{
		start = *i;
		skip_word((*cmd)->command, i);

		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, ft_substr((*cmd)->command, start, *i, g), g));
		printf("Word\n");
	}
}

void	ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh)
{
	int	i;

	i = 0;
	while ((*cmd)->command[i])
	{
		sort_split(cmd, &i, mini_sh, 0);
	}
	//printf("CMD SIZE : %d\n", ft_lst_parse_size((*cmd)->split_cmd));
}