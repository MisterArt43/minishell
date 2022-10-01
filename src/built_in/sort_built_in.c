/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:13:00 by abucia            #+#    #+#             */
/*   Updated: 2022/10/01 19:21:56 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	exec_built_in(t_global *mini_sh, t_lst_cmd **cmd)
{
	if (ft_nstrncmp((*cmd)->exec[0], "export", 7, 0) == 0)
	{
		b_in_export(cmd, mini_sh);
	}
	else if (!ft_strncmp((*cmd)->exec[0], "exit", -1))
	{
		b_in_exit(mini_sh);
	}
	else if (!ft_strncmp((*cmd)->exec[0], "pwd", -1))
	{
		b_in_pwd(mini_sh);
	}
	else if (!ft_strncmp((*cmd)->exec[0], "cd", -1))
	{
		b_in_cd(mini_sh);
	}
	else if (!ft_strncmp((*cmd)->exec[0], "echo", -1))
	{
		b_in_echo(mini_sh);
	}
	else if (!ft_strncmp((*cmd)->exec[0], "env", -1))
	{
		b_in_env(mini_sh);
	}
}

void	sort_build_in(t_lst_cmd **cmd, t_global *mini_sh)
{
	
}