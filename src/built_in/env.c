/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 03:09:59 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/01 20:53:11 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	b_in_env(t_global *mini_sh)
{
	if (!ft_strncmp(get_path(mini_sh), "NULL", -1))
	{
		ft_putendl_fd("wati-minishell: env: command not found", 2);
		return (127);
	}
	print_env(mini_sh->env);
	return (0);
}
