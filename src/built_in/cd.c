/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:05:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/01 17:50:22 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	change_path(t_global *mini_sh, char *key, char *newValue)
{
	int i;

	i = 0;
	while(mini_sh->env && ft_strncmp(mini_sh->env->key, key, -1))
	{
		mini_sh->env = mini_sh->env->next;
		i++;
	}	
	mini_sh->env->value = newValue;
	while (i)
	{
		mini_sh->env = mini_sh->env->prev;
		i--;
	}
}

int	b_in_cd(t_global *mini_sh)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	if (mini_sh->cmd->exec[1] && mini_sh->cmd->exec[2])
	{
		ft_putendl_fd("wati-minishell: cd: too many arguments", 2);
		return (1);
	}
	else if (mini_sh->cmd->exec[1])
	{
		if (!chdir(mini_sh->cmd->exec[1]))
		{
			change_path(mini_sh, "OLDPWD", pwd);
			getcwd(pwd, PATH_MAX);
			// change_path(mini_sh, "PWD", pwd);
			return (0);
		}
		else
		{
			ft_putstr_fd("wati-minishell: cd: ", 2);
			ft_putstr_fd(mini_sh->cmd->exec[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
	}
	return (1);
}