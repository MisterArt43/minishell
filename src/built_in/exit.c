/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:40:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/03 04:22:20 by tschlege         ###   ########lyon.fr   */
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

void	b_in_exit(t_global *mini_sh)
{
	if (mini_sh->cmd->exec[1] && check_exit_arg(mini_sh->cmd->exec[1]))
	{
		ft_putstr_fd("wati-minishell: exit: ", 2);
		ft_putstr_fd(mini_sh->cmd->exec[1], 2);
		ft_putendl_fd(": exit: numeric argument required", 2);
		mini_sh->ret = 255;
		quit(mini_sh);
	}
	else if (mini_sh->cmd->exec[1] && mini_sh->cmd->exec[2])
	{
		ft_putendl_fd("wati-minishell: exit: too many arguments", 2);
		mini_sh->ret = 1;
	}
	else if (mini_sh->cmd->exec[1])
	{
		mini_sh->ret = ft_atoi(mini_sh->cmd->exec[1]);
		printf("exit\n");
		quit(mini_sh);
	}
	else
	{
		printf("exit\n");
		mini_sh->ret = 0;
		quit(mini_sh);
	}
}
