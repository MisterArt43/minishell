/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbadge_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 01:07:26 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:08:50 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

//void *var est malloc dans l'appel de fonction
t_gc	*ft_gc_new(void *var, const char *er, t_global *g)
{
	t_gc	*newl;

	if (!var)
		malloc_exit(g, er);
	newl = malloc(sizeof(t_gc));
	if (!newl)
	{
		free(var);
		malloc_exit(g, "malloc error: new gc chain");
	}
	newl->src = var;
	newl->next = NULL;
	return (newl);
}

t_gc	*ft_gc_last(t_gc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	*ft_gc_add_front(t_gc **alst, t_gc *new)
{
	if (!new)
		return (NULL);
	new->next = *alst;
	*alst = new;
	return (new->src);
}

void	*ft_gc_add_back(t_gc **alst, t_gc *new)
{
	t_gc	*tmp;

	if (!alst || !new)
		return (NULL);
	if (!*alst)
	{
		*alst = new;
		return (new->src);
	}
	tmp = ft_gc_last(*alst);
	tmp->next = new;
	return (new->src);
}

void	ft_gc_delone(t_gc *lst)
{
	if (!lst)
		return ;
	if (!lst->src)
		return (free(lst));
	else
	{
		free(lst->src);
		free(lst);
	}
}
