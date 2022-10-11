/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:40:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/11 15:03:08 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	quit(t_global *mini_sh)
{
	ft_gc_clear(&mini_sh->gc_parsing);
	ft_lst_env_clear(&mini_sh->env);
	exit(mini_sh->ret);
}

int	check_exit_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	b_in_exit2(t_global *g)
{
	g->ret = 0;
}

void	b_in_exit(t_global *g)
{
	if (g->cmd->exec[1] && check_exit_arg(g->cmd->exec[1]))
	{
		ft_putstr_fd("wati-minishell: exit: ", 2);
		ft_putstr_fd(g->cmd->exec[1], 2);
		ft_putendl_fd(": exit: numeric argument required", 2);
		g->ret = 255;
	}
	else if (g->cmd->exec[1] && g->cmd->exec[2])
	{
		ft_putendl_fd("wati-minishell: exit: too many arguments", 2);
		g->ret = 1;
		return ;
	}
	else if (g->cmd->exec[1])
	{
		g->ret = ft_atoi(g->cmd->exec[1]);
		printf("exit\n");
	}
	else if (ft_lst_cmd_size(g->cmd) == 1)
		printf("exit\n");
	else
		return (b_in_exit2(g));
	quit(g);
}
