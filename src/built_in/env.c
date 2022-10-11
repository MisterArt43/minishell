/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:59 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/11 16:43:37 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	print_env(t_lst_env *env)
{
	while (env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	b_in_env(t_global *mini_sh, t_lst_cmd **cmd)
{
	if (check_no_arg(cmd, "env", mini_sh) == 0)
	{
		mini_sh->ret = 1;
		return ;
	}
	mini_sh->ret = 0;
	print_env(mini_sh->env);
}
