/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:55:58 by abucia            #+#    #+#             */
/*   Updated: 2022/10/03 04:01:06 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	do_unset(char **exec, t_lst_env *tmp, t_global *g)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		while (tmp)
		{
			if (ft_nstrncmp(exec[i], tmp->key, ft_strlen(tmp->key), 0) == 0)
			{
				ft_lst_env_del_in(tmp, g);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void	b_in_unset(t_lst_cmd **cmd, t_global *g)
{
	char		**exec;

	if (ft_strstrlen((*cmd)->exec) == 1)
		return ;
	g->ret = 0;
	if (!check_no_arg(cmd, "unset: usage: unset [-f] [-v] [name ...]", g))
	{
		g->ret = 2;
		return ;
	}
	exec = ft_split(rebuild_command(*cmd, g), ' ', g);
	do_unset(exec, g->env, g);
}
