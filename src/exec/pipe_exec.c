/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:23:29 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/04 19:13:41 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_builtin(t_lst_cmd *cmd)
{
	if (!ft_strncmp(cmd->exec[0], "exit", -1)
		|| !ft_strncmp(cmd->exec[0], "pwd", -1)
		|| !ft_strncmp(cmd->exec[0], "cd", -1)
		|| !ft_strncmp(cmd->exec[0], "echo", -1)
		|| !ft_strncmp(cmd->exec[0], "env", -1)
		|| !ft_strncmp(cmd->exec[0], "export", -1)
		|| !ft_strncmp(cmd->exec[0], "unset", -1))
		return (0);
	else
		return (1);
}

void exec_child(t_global *mini_sh, t_lst_cmd *cmd, int fd[2], int fd_in)
{
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
	check_fd_in(&fd[0], &fd[1], cmd, mini_sh);
	if (!is_builtin(cmd))
		exec_built_in(mini_sh, &cmd);
	else if (!check_path(mini_sh, cmd))
		if (execve(get_binary(mini_sh, cmd), cmd->exec, ft_split(get_path(mini_sh), ':', mini_sh)) == - 1)
			cmd_not_vld(mini_sh, cmd);
	perror("wati-minishell");
	exit(EXIT_FAILURE);
}

int	complicado(t_global *mini_sh, t_lst_cmd *cmd, int fd_in, pid_t *c_pid)
{
	int		fd[2];
	pid_t	child_pid;

	fd[0] = -1;
	fd[1] = -1;
	if (cmd->next && pipe(fd) < 0)
	{
		ft_putendl_fd("PIPE ERR", 2);
		return (1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		ft_putendl_fd("wati-minishell: fork: Resource temporarily unavailable", 2);
		return (1);
	}
	else if (child_pid == 0)
		exec_child(mini_sh, cmd, fd, fd_in);
	if (fd_in > 0)
		close(fd_in);
	if (fd[1] > 0)
		close(fd[1]);
	printf("--------PIPE--------DEBUG fd[1] : %d, fd_in : %d\n", fd[1], fd_in);
	printf("--------PIPE--------DEBUG fd[0] : %d, fd_in : %d\n", fd[0], fd_in);
	if (cmd->next)
		complicado(mini_sh, cmd->next, fd[0], c_pid);
	else
		*c_pid = child_pid;
	return (child_pid);
}
	//on pipe et check de pipe
	//plus tard check si heredoc
	//fork et verif de fork
	//exec child avec les bon fd
	//close des fd * 2
	//recursivite complicado avec les bons fds
	