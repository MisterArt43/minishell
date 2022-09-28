/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:39:49 by abucia            #+#    #+#             */
/*   Updated: 2022/09/28 11:06:11 by abucia           ###   ########lyon.fr   */
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
		|| str[*i] == '\'' \
		|| str[*i] == '<' \
		|| str[*i] == '>')
			return ;
		*i += 1;
	}
}

void	skip_redirection(char *str, int *i)
{
	char	c;

	c = str[*i];
	while (c == str[*i])
		*i += 1;
}

void	parse_quote(char *str, int *i, t_global *g, t_lst_cmd **cmd)
{
	int	start;

	start = *i + 1;
	skip_quote(str, i);
	ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, \
	ft_substr((*cmd)->command, start - 1, *i - start + 1, g), g));
	if (str[start] == 0)
		ft_lst_parse_last((*cmd)->split_cmd)->in_quote = ft_strdup("", g);
	else
		ft_lst_parse_last((*cmd)->split_cmd)->in_quote = \
		ft_substr((*cmd)->command, start, *i - start - 1, g);
}

void	sort_split(t_lst_cmd **cmd, int *i, t_global *g, int start)
{
	if ((*cmd)->command[*i] == '\'' || (*cmd)->command[*i] == '\"')
	{
		parse_quote((*cmd)->command, i, g, cmd);
		if (start - 1 >= 0 && checker_char_isempty((*cmd)->command[start - 1]) == 1)
			ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev = 1;
		printf("Quote / %d\n", ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev);
	}
	else if ((*cmd)->command[*i] == '<' || (*cmd)->command[*i] == '>')
	{
		skip_redirection((*cmd)->command, i);
		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, \
		ft_substr((*cmd)->command, start, *i - start, g), g));
		if (start - 1 >= 0 && checker_char_isempty((*cmd)->command[start - 1]) == 1)
			ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev = 1;
		printf("Redirect\n");
	}
	else
	{
		skip_word((*cmd)->command, i);
		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, \
		ft_substr((*cmd)->command, start, *i - start, g), g));
		if (start - 1 >= 0 && checker_char_isempty((*cmd)->command[start - 1]) == 1)
			ft_lst_parse_last((*cmd)->split_cmd)->is_near_prev = 1;
		printf("Word\n");
	}
}

t_lst_env	*cmp_env_key(int *i, char *str, t_global *g, t_lst_env	*tmp)
{
	int	j;
	int	tmp_i;

	if (!ft_isalnum(str[*i + 1]))
		return (NULL);
	while (tmp)
	{
		tmp_i = *i + 1;
		j = 0;
		if (tmp->key[j] == str[*i + 1])
		{
			while (1)
			{
				if (tmp->key[j] == 0 && ft_isalnum(str[tmp_i]) == 0)
				{
					*i = tmp_i;
					return (tmp);
				}
				if (str[tmp_i] != tmp->key[j] || !ft_isalnum(str[tmp_i]))
					break ;
				j++;
				tmp_i++;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	replace_env_var(t_lst_parse **lst, t_global *g)
{
	int	i;
	int start;
	int end;
	char *ret;
	t_lst_env	*find;

	if ((*lst)->str[0] == '\'')
		return ;
	i = 0;
	start = 0;
	ret = NULL;
	while ((*lst)->str[i])
	{
		if ((*lst)->str[i] == '$')
		{
			end = i;
			find = cmp_env_key(&i, (*lst)->str, g, g->env);
			if (find != NULL)
			{
				if (ret == NULL)
					ret = ft_strjoin(ft_substr((*lst)->str, start, end - start, g), find->value, g);
				else
					ret = ft_strjoin(ret, ft_strjoin(ft_substr((*lst)->str, start, end - start, g), find->value, g), g);
				start = i;
				i--;
			}
		}
		i++;
	}
	if (ret != NULL)
	{
		ret = ft_strjoin(ret, ft_substr((*lst)->str, start , i - start, g), g);
		(*lst)->env_var_str = ret;
		printf("->env var detected : before = '%s' after = '%s'\n", (*lst)->str, (*lst)->env_var_str);
	}
}

void	ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh)
{
	int			i;
	t_lst_parse	*lst_parse;

	i = 0;
	while ((*cmd)->command[i])
	{
		skip_to_next_word((*cmd)->command, &i);
		if (!(*cmd)->command[i] == 0)
			sort_split(cmd, &i, mini_sh, i);
	}
	lst_parse = (*cmd)->split_cmd;
	while (lst_parse)
	{
		replace_env_var(&lst_parse, mini_sh);
		lst_parse = lst_parse->next;
	}
}