/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:58:37 by abucia            #+#    #+#             */
/*   Updated: 2022/10/03 21:12:36 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	heredoc(t_lst_parse *tmp)
{
	int	fd[2];

	if (pipe(fd) < 0)
	{
		ft_putendl_fd("PIPE ERR", 2);
		return ;
	}
	write(fd[1], tmp->heredoc, ft_strlen(tmp->heredoc));
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

void	left_redirect(int *fd_in, t_lst_parse *tmp, t_global *g)
{
	if (*fd_in > 0)
		close(*fd_in);
	*fd_in = open(remove_quote(tmp->next->str, g), O_RDONLY);
	dup2(*fd_in, STDIN_FILENO);
	if (*fd_in > 0)
		close(*fd_in);
}

void	right_right_redirect(int *fd_in, int *fd_out, t_lst_parse *tmp, t_global *g)
{
	if (*fd_in > 0)
		close(*fd_in);
	if (*fd_out > 0)
		close(*fd_out);
	*fd_out = open(remove_quote(tmp->next->str, g), \
	O_CREAT | O_RDWR | O_APPEND, 777);
	dup2(*fd_out, STDOUT_FILENO);
	if (*fd_out > 0)
		close(*fd_out);
}

void	right_redirect(int	*fd_in, int *fd_out, t_lst_parse *tmp, t_global *g)
{
	if (*fd_in > 0)
		close(*fd_in);
	if (*fd_out > 0)
		close(*fd_out);
	*fd_out = open(remove_quote(tmp->next->str, g), O_CREAT | O_RDWR, 777);
	dup2(*fd_out, STDOUT_FILENO);
	if (*fd_out > 0)
		close(*fd_out);
}

//EXIT ?
void	check_fd_in(int *fd_in, int *fd_out, t_lst_cmd *cmd, t_global *g)
{
	t_lst_parse	*tmp;
	t_lst_parse	*tmp2;

	tmp2 = NULL;
	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 4 || tmp->type == 3)
			tmp2 = tmp;
		if (tmp->type == 6)
			if (!access(remove_quote(tmp->next->str, g), F_OK))
				if (check_file_dir(remove_quote(tmp->next->str, g), g, 1) == 2)
					left_redirect(fd_in, tmp, g);
		if (tmp->type == 5) // HEREDOC
			heredoc(tmp);
		tmp = tmp->next;
	}
	if (tmp2 != NULL)
	{
		if (tmp2->type == 4)
			right_redirect(fd_in, fd_out, tmp2, g);
		if (tmp2->type == 3)
			right_right_redirect(fd_in, fd_out, tmp2, g);
	}
}

void	exec_cmd(t_global *mini_sh)
{
	pid_t	pid = 0;
	int		status = 0;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini_sh->ret = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else 
	{
		if (pipe(mini_sh->cmd->fd) < 0)
		{
			ft_putendl_fd("PIPE ERR", 2);
			return ;
		}
		check_fd_in(&mini_sh->cmd->fd[0], &mini_sh->cmd->fd[1], \
		mini_sh->cmd, mini_sh);
		if (mini_sh->cmd->fd[0] > 0)
			close(mini_sh->cmd->fd[0]);
		if (mini_sh->cmd->fd[1] > 0)
			close(mini_sh->cmd->fd[1]);
		if (!check_path(mini_sh, mini_sh->cmd))
		{
			if (execve(get_binary(mini_sh, mini_sh->cmd), mini_sh->cmd->exec, \
			rebuild_env(mini_sh->env, mini_sh)) == -1)
				cmd_not_vld(mini_sh, mini_sh->cmd);
		}
		exit(EXIT_FAILURE);
	}
}
