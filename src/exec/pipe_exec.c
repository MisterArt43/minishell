/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:23:29 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/29 18:18:03 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	close_fd(t_global *mini_sh)
{
	
}

void exec_child(t_global *mini_sh, int fd, int fd_in)
{
	
}

int	complicado(t_global *mini_sh, int fd_in)
{
	int		fd[2];
	pid_t	child_pid;

	fd[0] = -1;
	fd[1] = -1;
	
	if (pipe(fd) < 0)
	{
		ft_putendl_fd("PIPE ERR", 2);
		return (1);
	}
	child_pid = fork();
	if (child_pid == -1)
		return (1);
	else if (child_pid > 0)
		exec_child(mini_sh, fd, fd_in);
	
}


	//on pipe et check de pipe
	//plus tard check si heredoc
	//fork et verif de fork
	//exec child avec les bon fd
	//close des fd * 2
	//recursivite complicado avec les bons fds