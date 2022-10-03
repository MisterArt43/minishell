/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:05:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/03 04:06:09 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*find_env_value(char *str, t_global *g, t_lst_env *tmp)
{
	int i;
	int	j;
	int	tmp_i;

	i = 0;
	while (tmp)
	{
		tmp_i = i;
		j = 0;
		if (tmp->key[j] == str[i])
		{
			while (1)
			{
				if (tmp->key[j] == 0 && ft_isalnum(str[tmp_i]) == 0)
				{
					i = tmp_i;
					return (tmp->value);
				}
				if (str[tmp_i] != tmp->key[j] || !ft_isalnum(str[tmp_i]))
					break ;
				j++;
				tmp_i++;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_value_of_key(t_global *mini_sh, t_lst_env **env, char *key, char *newValue)
{
	t_lst_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, -1))
			break;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->value);
		tmp->value = newValue;
	}
}

int	check_file_dir(char *str, t_global *g, int mode)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
		access parent directories: No such file or directory", 2);
		g->ret = 0;
		return (0);
	}
	if (access(ft_strjoin(ft_strjoin(pwd, "/", g), str, g), F_OK) != 0)
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin(ft_strjoin("wati-minishell: cd: ", \
		g), str, g), ": No such file or directory", g), 2);
		g->ret = 1;
		return (1);
	}
	else if (mode == 0)
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin(ft_strjoin("wati-minishell: cd: ", \
		g), str, g), ": Not a directory", g), 2);
		g->ret = 1;
		return (1);
	}
	else
		return (2);
}

void	b_in_cd(t_global *mini_sh, t_lst_cmd **cmd)
{
	char	pwd[PATH_MAX];
	int		i;

	i = 0;
	mini_sh->ret = 0;
	if (!getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
		access parent directories: No such file or directory", 2);
		mini_sh->ret = 0;
		return ;
	}
	if ((*cmd)->exec[1] == NULL)
	{
		if (!find_env_value("HOME", mini_sh, mini_sh->env))
		{
			ft_putendl_fd("wati-minishell: cd: HOME not set", 2);
			mini_sh->ret = 1;
			return ;
		}
		else if (!chdir(find_env_value("HOME", mini_sh, mini_sh->env)))
		{
			change_value_of_key(mini_sh, &mini_sh->env, "OLDPWD", ft_strdup(pwd, NULL));
			if (!getcwd(pwd, PATH_MAX))
			{
				ft_putendl_fd("wati-minishell: cd: HOME not set", 2);
				mini_sh->ret = 0;
				return ;
			}
			change_value_of_key(mini_sh, &mini_sh->env, "PWD", ft_strdup(pwd, NULL));
			mini_sh->ret = 0;
			return ;
		}
	}
	else if ((*cmd)->exec[1])
	{
		if (!chdir((*cmd)->exec[1]))
		{
			change_value_of_key(mini_sh, &mini_sh->env, "OLDPWD", ft_strdup(pwd, NULL));
			if (!getcwd(pwd, PATH_MAX))
			{
				ft_putendl_fd("cd: error retrieving current directory: \
				getcwd: cannot access parent directories: No such file \
				or directory", 2);
				mini_sh->ret = 0;
				return ;
			}
			change_value_of_key(mini_sh, &mini_sh->env, "PWD", ft_strdup(pwd, NULL));
			mini_sh->ret = 0;
			return ;
		}
		else
			check_file_dir((*cmd)->exec[1], mini_sh, 0);
		return ;
	}
		mini_sh->ret = 1;
		return ;
}



// #include "../../includes/header.h"

// void	change_value_of_key(t_global *mini_sh, t_lst_env **env, char *key, char *newValue)
// {
// 	t_lst_env	*tmp;

// 	tmp = *env;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->key, key, -1))
// 			break;
// 		tmp = tmp->next;
// 	}
// 	if (tmp)
// 	{
// 		free(tmp->value);
// 		tmp->value = newValue;
// 	}
// }

// int	b_in_cd(t_global *mini_sh, t_lst_cmd **cmd)
// {
// 	char	pwd[PATH_MAX];

// 	mini_sh->ret = 0;
// 	getcwd(pwd, PATH_MAX);
// 	if ((*cmd)->exec[1])
// 	{
// 		if (!chdir((*cmd)->exec[1]))
// 		{
// 			change_value_of_key(mini_sh, &mini_sh->env, "OLDPWD", ft_strdup(pwd, NULL));
// 			getcwd(pwd, PATH_MAX);
// 			change_value_of_key(mini_sh, &mini_sh->env, "PWD", ft_strdup(pwd, NULL));
// 			return (0);
// 		}
// 		else if (access(ft_strjoin(ft_strjoin(pwd, "/", mini_sh), (*cmd)->exec[1], mini_sh), F_OK) != 0)
// 		{
// 			ft_putstr_fd("wati-minishell: cd: ", 2);
// 			ft_putstr_fd((*cmd)->exec[1], 2);
// 			ft_putendl_fd(": No such file or directory", 2);
// 			return (1);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("wati-minishell: cd: ", 2);
// 			ft_putstr_fd((*cmd)->exec[1], 2);
// 			ft_putendl_fd(": Not a directory", 2);
// 			return (1);
// 		}
// 	}
// 	return (1);
// }