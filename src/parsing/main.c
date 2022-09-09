/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:50:14 by abucia            #+#    #+#             */
/*   Updated: 2022/08/30 16:50:14 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int print_er(const char *er)
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

	while (tab[i])
		i++;
	return (i);
}

void	parse_env(char *current, t_lst_env **lst_env)
{
	int	i;
	char *key;
	char *value;

	i = 0;
	while (current[i])
	{
		if (current[i] == '=')
		{
			key = ft_substr(current, 0, i, NULL);
			if (current[ i + 1] != 0)
				value = ft_substr(current, i + 1, ft_strlen(current) - i, NULL);
			else
				value = ft_strdup("", NULL);
			ft_lst_env_add_back(lst_env, ft_lst_env_new(&key, &value));
			return ;
		}
		i++;
	}
	printf("unhandled env in 'parse_env' function  : %s\n", current);
}

void	load_env(char **env, t_lst_env **lst_env)
{
	int	i;

	i = 0;
	if (env != NULL)
	{
		while (env[i])
		{
			parse_env(env[i], lst_env);
			i++;
		}
	}
}

void print_env(t_lst_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	make_lst_cmd(char *cmd, t_global *mini_sh)
{
	int	i;
	int	j;

	if (checker_isempty(cmd) == 0)
		return (0);
	if (check_pipe(cmd) == 0)
		return (print_er("minishell: syntax error near unexpected token `|'\n"));
	i = 0;
	while (cmd[i])
	{
		//printf("i : %d\n", i);
		j = 0;
		if (cmd[i] == '|')
		{
			ft_lst_cmd_add_back(&mini_sh->cmd, ft_lst_cmd_new(&mini_sh->gc_parsing, ft_substr(cmd, j, i - 1, &mini_sh->gc_parsing)));
			j = i + 1;
		}
		i++;
	}
	ft_lst_cmd_add_back(&mini_sh->cmd, ft_lst_cmd_new(&mini_sh->gc_parsing, ft_substr(cmd, j, i, &mini_sh->gc_parsing)));
	return (1);
}

void	start_parse(char *cmd, t_global *mini_sh)
{
	mini_sh->cmd = NULL;
	if (make_lst_cmd(cmd, mini_sh) == 0)
	{
		printf("invalid command, check start_parse function\n");
		ft_gc_clear(&mini_sh->gc_parsing);
		main_mini_sh(mini_sh);
	}
	printf("LST SIZE : %d\n",ft_lst_cmd_size(mini_sh->cmd));
	//test
	//t_lst_cmd *test = mini_sh->cmd;

	ft_split_shell(mini_sh->cmd->command, mini_sh);
	ft_gc_clear(&mini_sh->gc_parsing);
	main_mini_sh(mini_sh);
}

void	main_mini_sh(t_global *mini_sh)
{
	char *cmd;

	cmd = readline("wati-minishell> ");
	start_parse(cmd, mini_sh);
}

int	main(int argc, char **argv, char **env)
{
	t_global	mini_sh;
	t_lst_env	*tmp;

	mini_sh.env = NULL;
	mini_sh.cmd = NULL;
	mini_sh.gc_parsing = NULL;
	load_env(env, &mini_sh.env);
	main_mini_sh(&mini_sh);
	return (0);
}
