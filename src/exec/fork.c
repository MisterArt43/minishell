/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:58:37 by abucia            #+#    #+#             */
/*   Updated: 2022/10/01 21:30:29 by abucia           ###   ########lyon.fr   */
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
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (!get_path(mini_sh) || !ft_strncmp(get_path(mini_sh), "NULL", -1))
		{
			ft_putstr_fd("wati-minishell: ", 2);
			ft_putstr_fd(mini_sh->cmd->exec[0], 2);
			ft_putendl_fd(": command not found", 2);
			mini_sh->ret = 127;
			exit(EXIT_FAILURE);
		}
		else if (execve(get_binary(mini_sh, mini_sh->cmd), mini_sh->cmd->exec, ft_split(get_path(mini_sh), ':', mini_sh)) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

void	make_fork(t_global *mini_sh)
{
	int size;

	size = ft_lst_cmd_size(mini_sh->cmd);
}
