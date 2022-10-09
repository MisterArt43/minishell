/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:05:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/05 08:19:09 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_lst_env	*find_env_value(char *str, t_lst_env *tmp)
{
	t_dual_int	i;

	i.a = 0;
	while (tmp)
	{
		i.c = i.a;
		i.b = 0;
		if (tmp->key[i.b] == str[i.a])
		{
			while (1)
			{
				if (tmp->key[i.b] == 0 && ft_isalnum(str[i.c]) == 0)
				{
					i.a = i.c;
					return (tmp);
				}
				if (str[i.c] != tmp->key[i.b] || !ft_isalnum(str[i.c]))
					break ;
				i.b++;
				i.c++;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_value_of_key(t_lst_env **env, char *key, char *newValue)
{
	t_lst_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, -1))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->value);
		tmp->value = newValue;
	}
}

void	move_pwd(t_global *g, char *pwd, char *er)
{
	change_value_of_key(&g->env, "OLDPWD", ft_strdup(pwd, NULL));
	if (!getcwd(pwd, PATH_MAX))
		return (ft_putendl_fd(er, 2));
	change_value_of_key(&g->env, "PWD", ft_strdup(pwd, NULL));
	return ;
}

void	b_in_cd(t_global *mini_sh, t_lst_cmd **cmd)
{
	char	pwd[PATH_MAX];

	if (find_env_value("OLDPWD", mini_sh->env)->value == NULL)
		change_value_of_key(&mini_sh->env, "OLDPWD", ft_strdup("", NULL));
	if (!getcwd(pwd, PATH_MAX))
		return (ft_putendl_fd(CD_ERROR_LOST, 2));
	if ((*cmd)->exec[1] == NULL)
	{
		mini_sh->ret = 1;
		if (!find_env_value("HOME", mini_sh->env)->value)
			return (ft_putendl_fd("wati-minishell: cd: HOME not set", 2));
		else if (!chdir(find_env_value("HOME", mini_sh->env)->value))
			return (move_pwd(mini_sh, pwd, \
			"wati-minishell: cd: HOME not set"));
	}
	else if ((*cmd)->exec[1])
	{
		if (!chdir((*cmd)->exec[1]))
			return (move_pwd(mini_sh, pwd, CD_ERROR_LOST));
		check_file_dir((*cmd)->exec[1], mini_sh, 0);
		return ;
	}
	mini_sh->ret = 1;
}
