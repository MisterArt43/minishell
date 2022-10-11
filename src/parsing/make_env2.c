/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:21:22 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:21:22 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
