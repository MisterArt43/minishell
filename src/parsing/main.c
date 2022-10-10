/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:50:14 by abucia            #+#    #+#             */
/*   Updated: 2022/10/10 22:26:56 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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

int	strstrlen(char **tab)
{
	int	i;

	i = 0;

	while (tab[i])
		i++;
	return (i);
}

void	shlvl_plus_one(char **key, char **value, t_dual_int *forced_env)
{
	int	nb;

	if (ft_nstrncmp(*key, "SHLVL", 6, 0) == 0)
	{
		forced_env->a = 1;
		nb = ft_atoi(*value);
		free(*value);
		if (nb < 0)
			nb = -1;
		*value = ft_itoa(nb + 1, NULL);
	}
	else if (ft_nstrncmp(*key, "PWD", 6, 0) == 0)
		forced_env->b = 1;
	else if (ft_nstrncmp(*key, "OLDPWD", 6, 0) == 0)
		forced_env->c = 1;
}

void	parse_env(char *current, t_lst_env **lst_env, \
t_global *g, t_dual_int *forced_env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (current[i])
	{
		if (current[i] == '=')
		{
			key = ft_substr(current, 0, i, NULL);
			if (current[i + 1] != 0)
				value = ft_substr(current, i + 1, ft_strlen(current) - i, NULL);
			else
				value = ft_strdup("", NULL);
			shlvl_plus_one(&key, &value, forced_env);
			ft_lst_env_add_back(lst_env, ft_lst_env_new(&key, &value), g);
			return ;
		}
		i++;
	}
}

void	add_shlvl(t_lst_env **lst_env, t_global *g)
{
	char	*key;
	char	*value;

	key = ft_strdup("SHLVL", NULL);
	if (!key)
		malloc_exit(g, "error malloc ENV KEY");
	value = ft_strdup("1", NULL);
	if (!value)
	{
		free(key);
		malloc_exit(g, "error malloc ENV VALUE");
	}
	ft_lst_env_add_back(lst_env, ft_lst_env_new(&key, &value), g);
}

void	add_pwd(t_lst_env **lst_env, t_global *g)
{
	char	*key;
	char	*value;
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
	{
		key = ft_strdup("PWD", NULL);
		if (!key)
			malloc_exit(g, "error malloc ENV KEY");
		value = ft_strdup(pwd, NULL);
		if (!value)
		{
			free(key);
			malloc_exit(g, "error malloc ENV VALUE");
		}
		ft_lst_env_add_back(lst_env, ft_lst_env_new(&key, &value), g);
	}
}

void	add_oldpwd(t_lst_env **lst_env, t_global *g)
{
	char	*key;
	char	*value;

	key = ft_strdup("OLDPWD", NULL);
	if (!key)
		malloc_exit(g, "error malloc ENV KEY");
	value = NULL;
	ft_lst_env_add_back(lst_env, ft_lst_env_new(&key, &value), g);
}

void	add_env_(t_global *g)
{
	t_lst_env	*tmp;
	char		*key;
	char		*value;

	tmp = g->env;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->key, "_", 2, 0) == 0)
			return ;
		tmp = tmp->next;
	}
	key = ft_strdup("_", NULL);
	if (!key)
		malloc_exit(g, "MALLOC ERROR: ADD '_' ENV KEY");
	value = ft_strdup("/usr/bin/env", NULL);
	if (!value)
	{
		free(key);
		malloc_exit(g, "MALLOC ERROR: ADD '_' ENV KEY");
	}
	ft_lst_env_add_back(&g->env, ft_lst_env_new(&key, &value), g);
}

void	load_env(char **env, t_lst_env **lst_env, t_global *g)
{
	int			i;
	t_dual_int	forced_env;

	forced_env.a = 0;
	forced_env.b = 0;
	forced_env.c = 0;
	i = -1;
	if (env != NULL)
	{
		while (env[++i])
			parse_env(env[i], lst_env, g, &forced_env);
	}
	if (forced_env.a == 0)
		add_shlvl(lst_env, g);
	if (forced_env.b == 0)
		add_pwd(lst_env, g);
	if (forced_env.c == 0)
		add_oldpwd(lst_env, g);
	add_env_(g);
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
	pid_t	c_pid;
	pid_t	l_c_pid;

	c_pid = 1;
	l_c_pid = 1;
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
	{
		l_c_pid = complicado(g, g->cmd, 0, &c_pid);
		if (l_c_pid < 0)
		{
			printf("complicado \n");
			exit(1);
		}
		waitpid(c_pid, &status, 0);
		kill(c_pid, SIGTERM);
		waitpid(l_c_pid, &l_status, 0);
		if (WIFEXITED(l_status))
			g->ret = WEXITSTATUS(status);
		kill(l_c_pid, SIGTERM);
	}
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

void	sig_ctrl_d(t_global *mini_sh)
{
	write(1, "exit\n", 5);
	ft_gc_clear(&mini_sh->gc_parsing);
	ft_lst_env_clear(&mini_sh->env);
	exit(0);
}

void	main_mini_sh(t_global *mini_sh)
{
	while (1)
	{
		signal(SIGINT, (void *)sig_child_hndlr);
		signal(SIGQUIT, (void *)sig_child_hndlr);
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

void	static_signal(void	*ptr)
{
	static t_global	*g;

	if (ptr != NULL)
		g = ptr;
	else
		g->ret = 130;
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
		static_signal(&mini_sh);
		load_env(env, &mini_sh.env, &mini_sh);
		main_mini_sh(&mini_sh);
		return (0);
	}
}
