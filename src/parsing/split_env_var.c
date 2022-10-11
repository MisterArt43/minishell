/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:49:07 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 16:49:07 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_lst_env	*cmp_env_key(int *i, char *str, t_lst_env *tmp)
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

void	dollar_ret(t_global *g, char **ret, t_lst_parse **lst, t_dual_int *sub)
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

void	do_dollar(char **ret, t_dual_int *sub, t_lst_parse **lst, t_global *g)
{
	t_lst_env	*find;

	find = cmp_env_key(&sub->c, (*lst)->str, g->env);
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
		dollar_ret(g, ret, lst, sub);
}

void	new_lst(t_lst_parse **lst, t_lst_cmd **new_cmd, char *ret, t_global *g)
{
	spe_ec(new_cmd, ret, g);
	if (!*ret || !check_isempty((*new_cmd)->split_cmd->str))
	{
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		else if ((*lst)->next)
			(*lst) = (*lst)->next;
		else
			(*new_cmd)->fd[0] = 1;
	}
	else
		lst_magic(lst, new_cmd);
}

void	replace_env_v(t_lst_parse **lst, t_lst_cmd **cmd, t_global *g, char *r)
{
	t_dual_int	sub;
	t_lst_cmd	*new_cmd;

	if ((*lst)->str[0] == '\'')
		return ;
	sub.c = 0;
	sub.a = 0;
	while ((*lst)->str[sub.c])
	{
		sub.b = sub.c;
		if ((*lst)->str[sub.c] == '$')
			do_dollar(&r, &sub, lst, g);
		sub.c++;
	}
	if (r != NULL)
	{
		r = ft_strjoin(r, ft_substr((*lst)->str, sub.a, sub.c - sub.a, g), g);
		new_cmd = ft_lst_cmd_new(&g->gc_parsing, r, g);
		ft_split_shell(&new_cmd, g);
		new_lst(lst, &new_cmd, r, g);
		if (new_cmd->fd[0] == 1)
			(*lst)->str = ft_strdup("", g);
		else if (new_cmd->fd[0] == 2)
			(*cmd)->split_cmd = new_cmd->split_cmd;
	}
}
