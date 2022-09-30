/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:23:29 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/30 17:26:15 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void exec_child(t_global *mini_sh, t_lst_cmd *cmd, int fd[2], int fd_in)
{
	printf("%s: fd[0]=%d, fd[1]=%d, fd_in=%d\n", cmd->command, fd[0], fd[1], fd_in);
	if (fd[0] > 0)
		close(fd[0]);
	if  (fd_in > 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd[1] > 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	execve(get_binary(mini_sh, cmd), cmd->exec, ft_split(get_path(mini_sh), ':'));
	exit(0);
}

int	complicado(t_global *mini_sh, t_lst_cmd *cmd, int fd_in)
{
	int		fd[2];
	pid_t	child_pid;

	fd[0] = -1;
	fd[1] = -1;
	printf("jul\n");
	if (cmd->next && pipe(fd) < 0)
	{
		ft_putendl_fd("PIPE ERR", 2);
		return (1);
	}
	child_pid = fork();
	if (child_pid == -1)
		return (1);
	else if (child_pid == 0)
		exec_child(mini_sh, cmd, fd, fd_in);
	if (fd_in > 0) 
		close(fd_in);
	if (fd[1] > 0) 
		close(fd[1]);
	if (cmd->next)
		complicado(mini_sh, cmd->next, fd[0]);
	return (child_pid);
}


	//on pipe et check de pipe
	//plus tard check si heredoc
	//fork et verif de fork
	//exec child avec les bon fd
	//close des fd * 2
	//recursivite complicado avec les bons fds