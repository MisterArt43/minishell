/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:50:14 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:30:44 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	start_parse(char *cmd, t_global *mini_sh)
{
	t_lst_cmd	*tmp;

	mini_sh->cmd = NULL;
	if (make_lst_cmd(cmd, mini_sh, 0, 0) == 0)
	{
		ft_gc_clear(&mini_sh->gc_parsing);
		return (0);
	}
	tmp = mini_sh->cmd;
	while (tmp)
	{
		ft_split_shell(&tmp, mini_sh);
		tmp = tmp->next;
	}
	return (1);
}

void	select_exec(t_global *g, int status, int l_status)
{
	if (g->cmd->exec[0] != NULL && ft_lst_cmd_size(g->cmd) == 1 && \
		(!ft_strncmp(g->cmd->exec[0], "exit", -1) \
		|| !ft_strncmp(g->cmd->exec[0], "pwd", -1) \
		|| !ft_strncmp(g->cmd->exec[0], "cd", -1) \
		|| !ft_strncmp(g->cmd->exec[0], "echo", -1) \
		|| !ft_strncmp(g->cmd->exec[0], "env", -1) \
		|| !ft_strncmp(g->cmd->exec[0], "export", -1) \
		|| !ft_strncmp(g->cmd->exec[0], "unset", -1)))
		exec_built_in(g, &g->cmd);
	else if (ft_lst_cmd_size(g->cmd) == 1)
		exec_cmd(g, 0, 0);
	else if (ft_lst_cmd_size(g->cmd) > 1)
		kill_my_child(g, status, l_status);
}

int	check_line_and_init_gc(t_global *mini_sh)
{
	if (mini_sh->line[0] == 0)
	{
		free(mini_sh->line);
		return (1);
	}
	ft_gc_add_back(&mini_sh->gc_parsing, ft_gc_new(mini_sh->line, \
	"an error occured when mallocing readline", mini_sh));
	add_history(mini_sh->line);
	return (0);
}

void	main_mini_sh(t_global *mini_sh)
{
	while (1)
	{
		signal(SIGINT, (void *)sig_child_hndlr);
		signal(SIGQUIT, SIG_IGN);
		ft_gc_clear(&mini_sh->gc_parsing);
		mini_sh->in_cmd = 0;
		mini_sh->line = readline("wati-minishell> ");
		signal(SIGINT, (void *)sig_child_hndlr_in_cmd);
		signal(SIGQUIT, (void *)sig_child_hndlr_in_cmd);
		mini_sh->in_cmd = 1;
		if (mini_sh->line)
		{
			if (check_line_and_init_gc(mini_sh) == 1)
				continue ;
		}
		else
			sig_ctrl_d(mini_sh);
		if (start_parse(mini_sh->line, mini_sh) == 0)
			continue ;
		define_cmd(mini_sh);
		mini_sh->in_cmd = 1;
		select_exec(mini_sh, 0, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_global	mini_sh;

	if (argc > 0 && argv[0] != NULL)
	{
		mini_sh.env = NULL;
		mini_sh.cmd = NULL;
		mini_sh.gc_parsing = NULL;
		mini_sh.line = (char *) NULL;
		mini_sh.ret = 0;
		mini_sh.in_cmd = 0;
		static_signal(&mini_sh, 0);
		load_env(env, &mini_sh.env, &mini_sh);
		main_mini_sh(&mini_sh);
		return (0);
	}
}
