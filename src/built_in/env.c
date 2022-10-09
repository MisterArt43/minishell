/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:59 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/05 02:38:53 by tschlege         ###   ########lyon.fr   */
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

void	b_in_env(t_global *mini_sh)
{
	mini_sh->ret = 0;
	print_env(mini_sh->env);
}
