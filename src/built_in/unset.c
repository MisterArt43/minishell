/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:55:58 by abucia            #+#    #+#             */
/*   Updated: 2022/10/01 23:55:58 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	b_in_unset(t_lst_cmd **cmd, t_global *g)
{
	int			i;
	int			j;
	char		**exec;
	t_lst_env	*tmp;

	i = 0;
	tmp = g->env;
	exec = ft_split(rebuild_command(*cmd, g), ' ', g);
	while (exec[i])
	{
		while (tmp)
		{
			if (ft_nstrncmp(exec[i], tmp->key, ft_strlen(tmp->key), 0) == 0)
			{
				ft_lst_env_del_in(tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}