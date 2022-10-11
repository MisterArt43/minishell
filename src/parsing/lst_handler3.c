/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:15:32 by tschlege          #+#    #+#             */
/*   Updated: 2022/10/11 19:15:54 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ft_lst_env_add_back(t_lst_env **alst, t_lst_env *new, t_global *g)
{
	t_lst_env	*tmp;

	if (!new)
		malloc_exit(g, "malloc error NEW ENV");
	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = ft_lst_env_last(*alst);
	tmp->next = new;
	new->prev = tmp;
}

void	ft_lst_env_del_in(t_lst_env *lst, t_global *g)
{
	if (lst->prev != NULL && ft_nstrncmp(lst->key, "_", 2, 0) != 0)
	{
		if (lst->next != NULL)
			lst->prev->next = lst->next;
		else
			lst->prev->next = NULL;
	}
	else
	{
		if (lst->next != NULL && ft_nstrncmp(lst->key, "_", 2, 0) != 0)
		{
			lst->next->prev = NULL;
			g->env = g->env->next;
		}
		else
			return ;
	}
	if (!lst)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_lst_env_delone(t_lst_env *lst)
{
	if (!lst)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_lst_env_clear(t_lst_env **lst)
{
	t_lst_env	*tmp;
	t_lst_env	*tmp2;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_lst_env_delone(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}

int	ft_lst_env_size(t_lst_env *lst)
{
	unsigned int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
