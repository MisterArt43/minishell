/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:04:43 by abucia            #+#    #+#             */
/*   Updated: 2022/09/20 03:04:43 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_valid_key(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
			{
				printf("bash: export: `=': not a valid identifier");
				return (0);
			}
			else if (str[i + 1] == 0)
				return (2);
			else
				return (1);
		}
		else if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (3);
}

int	check_no_arg(t_lst_cmd **cmd)
{
	t_lst_parse *tmp;

	tmp = (*cmd)->split_cmd;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->str, "-", 1, 0))
		{
			printf("bash: export: %s: invalid option\n", tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void print_env(t_lst_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	exec_export(t_lst_cmd *cmd, t_global *mini_sh)
{
	if (ft_lst_parse_size(cmd->split_cmd) == 2)
	{
		//if (check_valid_key(cmd->split_cmd->next->str))
		//ft_lst_env_add_back(ft_lst_env_new())
	}
}

int	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{
	if (ft_strlen((*cmd)->exec) > 1)
	{
		if (ft_lst_cmd_size(*cmd) != 1)
			return (1);
		if (check_no_arg(cmd) == 0)
			return (0);

	}
	else
		print_env(mini_sh->env);
}