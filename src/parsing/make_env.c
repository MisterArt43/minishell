/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:16:54 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:16:54 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
