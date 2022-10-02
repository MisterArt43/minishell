/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:05:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/01 21:12:18 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	change_value_of_key(t_global *mini_sh, t_lst_env **env, char *key, char *newValue)
{
	t_lst_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, -1))
			break;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->value);
		tmp->value = newValue;
	}
}

int	b_in_cd(t_global *mini_sh)
{
	char	pwd[PATH_MAX];

	mini_sh->ret = 0;
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
			change_value_of_key(mini_sh, &mini_sh->env, "OLDPWD", ft_strdup(pwd, NULL));
			getcwd(pwd, PATH_MAX);
			change_value_of_key(mini_sh, &mini_sh->env, "PWD", ft_strdup(pwd, NULL));
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