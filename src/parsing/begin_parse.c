/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:30:22 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:30:22 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	kill_my_child(t_global *g, int status, int l_status)
{
	pid_t	c_pid;
	pid_t	l_c_pid;

	c_pid = -1;
	l_c_pid = -1;
	l_c_pid = complicado(g, g->cmd, 0, &c_pid);
	if (l_c_pid < 0 || c_pid < 0)
	{
		while (wait(NULL) != -1)
			;
		return ;
	}
	waitpid(c_pid, &status, 0);
	kill(c_pid, SIGTERM);
	waitpid(l_c_pid, &l_status, 0);
	if (WIFEXITED(l_status))
		g->ret = WEXITSTATUS(status);
	kill(l_c_pid, SIGTERM);
	while (wait(NULL) != -1)
		;
}

int	print_er(const char *er)
{
	int	i;

	i = 0;
	while (er[i])
	{
		write(2, &er[i], 1);
		i++;
	}
	return (0);
}

int	make_lst_cmd(char *cmd, t_global *mini_sh, int i, int j)
{
	if (check_isempty(cmd) == 0)
		return (0);
	if (check_pipe(cmd, 0, 0) == 0)
		return (print_er("minishell: syntax error near unexpected token `|'\n"));
	if (check_redirection(cmd, 0, 0) == 0)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			ft_lst_cmd_add_back(&mini_sh->cmd, ft_lst_cmd_new(\
			&mini_sh->gc_parsing, ft_substr(cmd, j, i - j, mini_sh), mini_sh));
			j = i + 1;
		}
		i++;
	}
	ft_lst_cmd_add_back(&mini_sh->cmd, ft_lst_cmd_new(\
	&mini_sh->gc_parsing, ft_substr(cmd, j, i - j, mini_sh), mini_sh));
	return (1);
}
