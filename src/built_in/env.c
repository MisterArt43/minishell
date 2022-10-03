/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:59 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/03 03:49:40 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	b_in_env(t_global *mini_sh, t_lst_cmd **cmd)
{
	mini_sh->ret = 0;
	if (check_no_arg(cmd, "env", mini_sh) == 0)
		return ;
	if (!ft_strncmp(get_path(mini_sh), "NULL", -1))
	{
		ft_putendl_fd("wati-minishell: env: command not found", 2);
		mini_sh->ret = 127;
	}
	print_env(mini_sh->env);
}

void print_env(t_lst_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}