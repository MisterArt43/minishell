/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:39:49 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 22:07:08 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	parse_quote(char *str, int *i, t_global *g, t_lst_cmd **cmd)
{
	int	start;

	start = *i + 1;
	skip_quote(str, i);
	if (str[*i] == 0)
		ft_strjoin(str, &str[start - 1], g);
	ft_lst_parse_add_back(&(*cmd)->split_cmd, \
	ft_lst_parse_new(&g->gc_parsing, \
	ft_substr((*cmd)->command, start - 1, *i - start + 1, g), g));
	if (str[start] == 0)
		(ft_lst_parse_last((*cmd)->split_cmd))->in_quote = ft_strdup("", g);
	else
		(ft_lst_parse_last((*cmd)->split_cmd))->in_quote = \
		ft_substr((*cmd)->command, start, *i - start - 1, g);
}

void	sort_split(t_lst_cmd **cmd, int *i, t_global *g, int beg)
{
	if ((*cmd)->command[*i] == '\'' || (*cmd)->command[*i] == '\"')
	{
		parse_quote((*cmd)->command, i, g, cmd);
		if (beg - 1 >= 0 && check_char_isempty((*cmd)->command[beg - 1]) == 1)
			ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev = 1;
	}
	else if ((*cmd)->command[*i] == '<' || (*cmd)->command[*i] == '>')
	{
		skip_redirection((*cmd)->command, i);
		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(\
		&g->gc_parsing, ft_substr((*cmd)->command, beg, *i - beg, g), g));
		if (beg - 1 >= 0 && check_char_isempty((*cmd)->command[beg - 1]) == 1)
			ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev = 1;
	}
	else
	{
		skip_word((*cmd)->command, i);
		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(\
		&g->gc_parsing, ft_substr((*cmd)->command, beg, *i - beg, g), g));
		if (beg - 1 >= 0 && check_char_isempty((*cmd)->command[beg - 1]) == 1)
			ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev = 1;
	}
}

void	ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh)
{
	char		*r;
	int			i;
	t_lst_parse	*lst_parse;

	i = 0;
	while ((*cmd)->command[i])
	{
		skip_to_next_word((*cmd)->command, &i);
		if ((*cmd)->command[i] != 0)
			sort_split(cmd, &i, mini_sh, i);
	}
	lst_parse = (*cmd)->split_cmd;
	while (lst_parse)
	{
		r = NULL;
		replace_env_v(&lst_parse, cmd, mini_sh, r);
		lst_parse = lst_parse->next;
	}
}
