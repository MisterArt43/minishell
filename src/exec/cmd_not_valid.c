/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:43:26 by tschlege          #+#    #+#             */
/*   Updated: 2022/10/03 21:32:19 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	cmd_not_vld(t_global *mini_sh, t_lst_cmd *cmd)
{
	ft_putstr_fd("wati-minishell: ", 2);
	ft_putstr_fd(cmd->exec[0], 2);
	ft_putendl_fd(": command not found", 2);
	mini_sh->ret = 127;
	ft_gc_clear(&mini_sh->gc_parsing);
	ft_lst_env_clear(&mini_sh->env);
	exit(127);
}
