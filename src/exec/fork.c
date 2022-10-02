/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:58:37 by abucia            #+#    #+#             */
/*   Updated: 2022/10/02 22:43:22 by tschlege         ###   ########lyon.fr   */
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
		if (WIFEXITED(status))
    		printf("Child exited with RC=%d\n", WEXITSTATUS(status));
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
