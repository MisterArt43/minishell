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

//EXIT ?
void	check_fd_in(int *fd_in, t_lst_cmd *cmd, t_global *g)
{
	t_lst_parse *tmp;

	tmp = cmd->split_cmd;
	while (tmp)
	{
		printf("WAS HERE : %d\n", tmp->type);
		if (tmp->type == 5 || tmp->type == 6)
		{
			if (tmp->type == 6)
			{
				if (!access(remove_quote(tmp->next->str, g), F_OK))
				{
					if (check_file_dir(remove_quote(tmp->next->str, g), g, 1) == 2)
					{
						if (*fd_in > 0)
							close(*fd_in);
						*fd_in = open(remove_quote(tmp->next->str, g), O_RDONLY);
						dup2(*fd_in, STDIN_FILENO);
						if (*fd_in < 0)
							close(*fd_in);
					}
				}
				else
					printf("ERROR ACCESS\n");
			}
			else //HEREDOC
			{
				if (*fd_in > 0)
				{
					printf("HEREDOC : %s\n", tmp->heredoc);
					write(*fd_in, tmp->heredoc, ft_strlen(tmp->heredoc));
					dup2(*fd_in, STDIN_FILENO);
					close(*fd_in);
				}
				else
					printf("CANT REDIRECT HEREDOC\n");
			}
		}
		tmp = tmp->next;
	}
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
		if (pipe(mini_sh->cmd->fd) < 0)
		{
			ft_putendl_fd("PIPE ERR", 2);
			return ;
		}
		check_fd_in(&mini_sh->cmd->fd[0], mini_sh->cmd, mini_sh);
		if (mini_sh->cmd->fd[0] > 0)
			close(mini_sh->cmd->fd[0]);
		if (mini_sh->cmd->fd[1] > 0)
			close(mini_sh->cmd->fd[1]);
		printf("-------------------DEBUG fd[1] : %d, fd_in : %d\n", mini_sh->cmd->fd[1], mini_sh->cmd->fd[0]);
		printf("-------------------DEBUG fd[0] : %d, fd_in : %d\n", mini_sh->cmd->fd[0], mini_sh->cmd->fd[0]);
		// Le processus enfant execute la commande ou exit si execve echoue
		if (!check_path(mini_sh, mini_sh->cmd)) // si un binary
		{
			if (execve(get_binary(mini_sh, mini_sh->cmd), mini_sh->cmd->exec, \
			rebuild_env(mini_sh->env, mini_sh)) == -1)
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
