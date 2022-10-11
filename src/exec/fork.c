/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:58:37 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 18:31:12 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	close_fds(int *fd_in, int *fd_out)
{
	if (*fd_in > 1)
		close(*fd_in);
	if (*fd_out > 1)
		close(*fd_out);
}

void	check_fd_out(int *fd_in, int *fd_out, t_lst_parse *tmp, t_global *g)
{
	if (tmp->type == 4)
		right_redirect(fd_in, fd_out, tmp, g);
	else if (tmp->type == 3)
		right_right_redirect(fd_in, fd_out, tmp, g);
}

int	sig_child_hndlr_in_cmd(const int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		if (signal == SIGINT)
		{
			write(1, "\n", 1);
			static_signal(NULL, 130);
		}
		else if (signal == SIGQUIT)
		{
			write(1, "Quit\n", 5);	
			static_signal(NULL, 131);
		}
	}
	return (130);
}

int	sig_child_hndlr(const int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("\0", 1);
		write(1, "\n", 1);
		rl_redisplay();
		static_signal(NULL, 0);
	}
	return (130);
}

int	check_has_cmd(t_lst_cmd *cmd, t_global *g)
{
	if (cmd->exec[0] == NULL)
	{
		ft_lst_env_clear(&g->env);
		ft_gc_clear(&g->gc_parsing);
		return (0);
	}
	return (1);
}

void	exec_cmd(t_global *g, pid_t pid, int status)
{
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g->ret = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else
	{
		if (pipe(g->cmd->fd) < 0)
			return (ft_putendl_fd("PIPE ERR", 2));
		check_fd_in(&g->cmd->fd[0], &g->cmd->fd[1], \
		g->cmd, g);
		close_fds(&g->cmd->fd[0], &g->cmd->fd[1]);
		if (check_has_cmd(g->cmd, g) && !check_path(g, g->cmd))
		{
			if (execve(get_binary(g, g->cmd), g->cmd->exec, \
			rebuild_env(g->env, g)) == -1)
				cmd_not_vld(g, g->cmd);
		}
		exit(EXIT_FAILURE);
	}
}
