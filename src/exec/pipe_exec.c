/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:23:29 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/11 15:27:28 by tschlege         ###   ########lyon.fr   */
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

void	exec_child(t_global *mini_sh, t_lst_cmd *cmd, int fd[2], int fd_in)
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd_in > 0)
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
	else if (check_has_cmd(cmd, mini_sh) && !check_path(mini_sh, cmd))
	{
		if (execve(get_binary(mini_sh, cmd), cmd->exec, \
		ft_split(get_path(mini_sh), ':', mini_sh)) == -1)
			cmd_not_vld(mini_sh, cmd);
		perror("wati-minishell");
		exit(EXIT_FAILURE);
	}
	exit(mini_sh->ret);
}

int	fork_override(int fd[2], pid_t child_pid)
{
	ft_putendl_fd(FORK_OVERRIDE, 2);
	// rl_on_new_line();
	// rl_replace_line("\0", 1);
	// write(1, "\n", 1);
	// rl_redisplay();
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
	return (child_pid);
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
		return (fork_override(fd, child_pid));
	else if (child_pid == 0)
		exec_child(mini_sh, cmd, fd, fd_in);
	close_fds(&fd_in, &fd[1]);
	if (cmd->next)
		complicado(mini_sh, cmd->next, fd[0], c_pid);
	else
		*c_pid = child_pid;
	return (child_pid);
}
