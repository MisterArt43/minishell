/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:58:37 by abucia            #+#    #+#             */
/*   Updated: 2022/10/02 23:00:37 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	check_fd_in(int *fd_in, t_lst_cmd *cmd, t_global *g)
{
	t_lst_parse *tmp;

	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 5 || tmp->type == 6)
		{
			if (tmp->type == 6)
			{
				access(remove_quote(tmp->str, g), F_OK);

			}

			if (*fd_in > 0)
				close(*fd_in);
		}
		tmp->next;
	}
	
}

void	redirect_fork(t_global *g)
{
	if (g->cmd->fd_in > 0)
		if (dup2(g->cmd->fd_in, STDIN_FILENO))
			malloc_exit(g, "malloc error dup2");
	if (g->cmd->fd_out > 0)
	{
		if (dup2(g->cmd->fd_out, STDOUT_FILENO))
		{
			close(g->cmd->fd_in);
			malloc_exit(g, "malloc error dup2");
		}
	}
	if (g->cmd->fd_in > 0)
		close(g->cmd->fd_in);
	if (g->cmd->fd_out > 0)
		close(g->cmd->fd_out);
}

void	exec_cmd(t_global *mini_sh)
{
	// printf("CMD TO EXEC: $%s$, ENV: $%s$\n", mini_sh->cmd->exec[0], mini_sh->env->value);
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0)
	{
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
    		mini_sh->ret = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else 
	{
		// Le processus enfant execute la commande ou exit si execve echoue
		if (!check_path(mini_sh, mini_sh->cmd)) // si un binary
		{
			if (execve(get_binary(mini_sh, mini_sh->cmd), mini_sh->cmd->exec, rebuild_env(mini_sh->env, mini_sh)) == -1)
				cmd_not_vld(mini_sh, mini_sh->cmd);
		}
		exit(EXIT_FAILURE);
	}
}

void	make_fork(t_global *mini_sh)
{
	int size;

	size = ft_lst_cmd_size(mini_sh->cmd);
}
