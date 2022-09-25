/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:04:43 by abucia            #+#    #+#             */
/*   Updated: 2022/09/20 03:04:43 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_no_arg(t_lst_cmd **cmd)
{
	t_lst_parse *tmp;

	tmp = (*cmd)->split_cmd;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->str, "-", 1, 0))
		{
			printf("bash: export: %s: invalid option\n", tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_valid_key(char *str)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while(str[i])
	{
		if (checker_char_isempty(str[i]) != 0 && str[i] != '=')
			state = 1;
		if (str[i] == '=')
		{
			if (i == 0 || (state == 0 && (str[0] == '\"' || str[0] == '\'')))
			{
				printf("bash: export: `=': not a valid identifier");
				return (0);
			}
			else if (str[i + 1] == 0)
				return (2);
			else
				return (1);
		}
		else if (!ft_isalnum(str[i]))
			if (!(i == 0 && (str[i] == '\"' || str[i] == '\'')))
				return (0);
		i++;
	}
	return (3);
}

void print_env(t_lst_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	sort_export(int *i, char *str, t_lst_cmd *cmd)
{
	t_lst_parse *tmp;

	tmp = cmd->split_cmd;
	while (ft_nstrncmp(str, tmp->env_var_str, ft_strlen(str), 0) != 0)
	{
		tmp = tmp->next;
	}
	
}

//faire attention au redirection et fichier a ignorer
void	exec_export(t_lst_cmd *cmd, t_global *mini_sh)
{
	int	i;
	int	nb;

	nb = ft_strlen(cmd->exec);
	i = 1;
	while (cmd->exec[i])
	{
		if (nb == 2 && check_valid_key(cmd->exec[i]) == 3)
		{
			ft_lst_env_add_back(&mini_sh->env, ft_lst_env_new(&, &ft_strdup("")))
		}
		i++;
	}
	
}

int	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{
	if (ft_strlen((*cmd)->exec) > 1)
	{
		if (ft_lst_cmd_size(*cmd) != 1)
			return (1);
		if (check_no_arg(cmd) == 0)
			return (0);

	}
	else
		print_env(mini_sh->env);
}