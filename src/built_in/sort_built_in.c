/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:13:00 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 16:36:20 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	exec_built_in(t_global *mini_sh, t_lst_cmd **cmd)
{
	(*cmd)->fd[0] = 1;
	(*cmd)->fd[1] = 1;
	check_fd_in(&(*cmd)->fd[0], &(*cmd)->fd[1], *cmd, mini_sh);
	if (!ft_strncmp((*cmd)->exec[0], "exit", -1))
		b_in_exit(mini_sh);
	mini_sh->ret = 0;
	if (ft_nstrncmp((*cmd)->exec[0], "export", 7, 0) == 0)
		b_in_export(cmd, mini_sh);
	else if (!ft_strncmp((*cmd)->exec[0], "pwd", -1))
		b_in_pwd(mini_sh);
	else if (!ft_strncmp((*cmd)->exec[0], "cd", -1))
		b_in_cd(mini_sh, cmd);
	else if (!ft_strncmp((*cmd)->exec[0], "echo", -1))
		b_in_echo(mini_sh, cmd);
	else if (!ft_strncmp((*cmd)->exec[0], "env", -1))
		b_in_env(mini_sh, cmd);
	else if (!ft_nstrncmp((*cmd)->exec[0], "unset", 6, 0))
		b_in_unset(cmd, mini_sh);
	dup2(STDOUT_FILENO, 1);
	dup2(STDIN_FILENO, 1);
}
