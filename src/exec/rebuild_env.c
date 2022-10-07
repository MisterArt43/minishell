/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:43:47 by abucia            #+#    #+#             */
/*   Updated: 2022/10/02 20:14:55 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*rebuild_env_tab(t_lst_env *current, t_global *g)
{
	char	*res;

	if (current->value == NULL)
		return (NULL);
	res = ft_strdup(current->key, g);
	res = ft_strjoin(res, "=", g);
	res = ft_strjoin(res, current->value, g);
	return (res);
}

char	**rebuild_env(t_lst_env *env, t_global *g)
{
	t_lst_env	*tmp;
	char		**res;
	int			i;

	i = 0;
	tmp = env;
	res = ft_gc_add_back(&g->gc_parsing, \
	ft_gc_new(malloc((ft_lst_env_size(env) + 1) * sizeof(char *)), \
	"malloc error in rebuild env", g));
	while (tmp)
	{
		res[i] = rebuild_env_tab(tmp, g);
		if (res != NULL)
			i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}
