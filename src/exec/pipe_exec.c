/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wati-Theo <wati-theo@protonmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:23:29 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/29 23:23:29 by Wati-Theo        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	complicado(t_global *mini_sh, int fd_in)
{
	int		fd[2];
	pid_t	child_pid;
	//on pipe
	//plus tard check si heredoc
	//fork et verif de fork
	//exec child avec les bon fd
	//close des fd * 2
	//recursivite complicado avec les bons fds
}