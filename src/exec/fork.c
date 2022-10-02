/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:58:37 by abucia            #+#    #+#             */
/*   Updated: 2022/10/02 19:16:41 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
		kill(pid, SIGTERM);
	}
	else 
	{
		// Le processus enfant execute la commande ou exit si execve echoue
		if ((access(mini_sh->cmd->exec[0], F_OK) == 0) && check_path(mini_sh, mini_sh->cmd)) // si ./binary
		{
			if (execve((const char *)mini_sh->cmd->exec[0], (char * const *)mini_sh->cmd, ft_split(get_path(mini_sh), ':', mini_sh)) == -1)
				cmd_not_vld(mini_sh, mini_sh->cmd);	
		}
		else if (!check_path(mini_sh, mini_sh->cmd)) // si un binary
		{
			if (execve(get_binary(mini_sh, mini_sh->cmd), mini_sh->cmd->exec, ft_split(get_path(mini_sh), ':', mini_sh)) == -1)
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
