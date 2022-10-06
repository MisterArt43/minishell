/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:39:49 by abucia            #+#    #+#             */
/*   Updated: 2022/09/30 15:50:23 by abucia           ###   ########lyon.fr   */
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

t_lst_env	*cmp_env_key(int *i, char *str, t_global *g, t_lst_env	*tmp)
{
	int	j;
	int	tmp_i;

	if (!ft_isalnum(str[*i + 1]))
		return (NULL);
	while (tmp)
	{
		tmp_i = *i;
		j = -1;
		if (tmp->key[j + 1] == str[*i + 1])
		{
			while (1 && ++j != -2 && ++tmp_i != -2)
			{
				if (tmp->key[j] == 0 && ft_isalnum(str[tmp_i]) == 0)
				{
					*i = tmp_i;
					return (tmp);
				}
				if (str[tmp_i] != tmp->key[j] || !ft_isalnum(str[tmp_i]))
					break ;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_lst_cmd	*do_dollar(char **ret, t_dual_int *sub, t_lst_parse **lst, t_global *g)
{
	t_lst_env	*find;
	t_lst_cmd	*new_cmd;

	find = cmp_env_key(&sub->c, (*lst)->str, g, g->env);
	if (find != NULL)
	{
		if (*ret == NULL)
			*ret = ft_strjoin(ft_substr((*lst)->str, sub->a, sub->b - sub->a, \
			g), find->value, g);
		else
			*ret = ft_strjoin(*ret, ft_strjoin(ft_substr((*lst)->str, sub->a, \
			sub->b - sub->a, g), find->value, g), g);
		sub->a = sub->c;
		sub->c--;
	}
	else if ((*lst)->str[sub->c + 1] == '?')
	{
		if (*ret == NULL)
			*ret = ft_strjoin(ft_substr((*lst)->str, sub->a, sub->b - sub->a, \
			g), ft_itoa(g->ret, g), g);
		else
			*ret = ft_strjoin(*ret, ft_strjoin(ft_substr((*lst)->str, sub->a, \
			sub->b - sub->a, g), ft_itoa(g->ret, g), g), g);
		sub->c++;
		sub->a = sub->c + 1;
	}
}

void	replace_env_var(t_lst_parse **lst, t_lst_cmd **cmd, t_global *g)
{
	t_dual_int	sub;
	char		*ret;
	t_lst_cmd	*new_cmd;

	if ((*lst)->str[0] == '\'')
		return ;
	sub.c = 0;
	sub.a = 0;
	ret = NULL;
	while ((*lst)->str[sub.c])
	{
		if ((*lst)->str[sub.c] == '$')
		{
			sub.b = sub.c;
			do_dollar(&ret, &sub, lst, g);
		}
		sub.c++;
	}
	if (ret != NULL)
	{
		ret = ft_strjoin(ret, \
		ft_substr((*lst)->str, sub.a, sub.c - sub.a, g), g);
		printf("#### RET : %s\n", ret);
		if (ret[0] == "\"" || ret[0] == "\'")
		new_cmd = ft_lst_cmd_new(&g->gc_parsing, ret, g);
		ft_split_shell(&new_cmd, g);
		if (*ret == 0 || check_isempty(new_cmd->split_cmd->str) == 0)
		{

			if ((*lst)->next)
				(*lst)->next->prev = (*lst)->prev;
			if ((*lst)->prev)
				(*lst)->prev->next = (*lst)->next;
			else if ((*lst)->next)
				(*lst) = (*lst)->next;
			else {
				(*lst)->str = ft_strdup("", g);
			}
		}
		else 
		{
			new_cmd->split_cmd->is_near_prev = (*lst)->is_near_prev;
			new_cmd->split_cmd->prev = (*lst)->prev;
			if ((*lst)->prev)
				(*lst)->prev->next = new_cmd->split_cmd;
			else
				(*cmd)->split_cmd = new_cmd->split_cmd;
			if ((*lst)->next)
				(*lst)->next->prev = ft_lst_parse_last(new_cmd->split_cmd);
			ft_lst_parse_last(new_cmd->split_cmd)->next = (*lst)->next;
			(*lst)->next = new_cmd->split_cmd;
			*lst = new_cmd->split_cmd;
		}
		// (*lst)->env_var_str = ret;
	}
}

void breakpoints(void)
{
	return ;
}

void	ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh)
{
	int			i;
	t_lst_parse	*lst_parse;
	printf(" -- NEW COMMAND  :  %s\n", (*cmd)->command);

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
		breakpoints();
		printf("BEFORE : %s\n", lst_parse->str);
		replace_env_var(&lst_parse, cmd, mini_sh);
		printf("AFTER : %s\n --- ------- --- \n", lst_parse->str);
		breakpoints();
		lst_parse = lst_parse->next;
	}
}
