/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 01:06:50 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:14:53 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_lst_cmd	*ft_lst_cmd_new(t_gc **cmd_gc, char *cmd, t_global *g)
{
	t_lst_cmd	*newl;

	newl = (t_lst_cmd *)ft_gc_add_back(cmd_gc, ft_gc_new(malloc(sizeof(\
	t_lst_cmd)), "An error occur while mallocing cmd", g));
	if (!newl)
		return (NULL);
	newl->next = NULL;
	newl->split_cmd = NULL;
	newl->command = cmd;
	newl->fd[0] = -1;
	newl->fd[1] = -1;
	return (newl);
}

t_lst_cmd	*ft_lst_cmd_last(t_lst_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_cmd_add_back(t_lst_cmd **alst, t_lst_cmd *new)
{
	t_lst_cmd	*tmp;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = ft_lst_cmd_last(*alst);
	tmp->next = new;
}

int	ft_lst_cmd_size(t_lst_cmd *lst)
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

//---------------------

t_lst_parse	*ft_lst_parse_new(t_gc **cmd_gc, char *cmd, t_global *g)
{
	t_lst_parse	*newl;

	newl = (t_lst_parse *)ft_gc_add_back(cmd_gc, ft_gc_new(malloc(sizeof(\
	t_lst_parse)), "An error occur while mallocing parsed cmd", g));
	if (!newl)
		return (NULL);
	newl->next = NULL;
	newl->prev = NULL;
	newl->env_var_str = NULL;
	newl->str = cmd;
	newl->type = 0;
	newl->is_near_prev = 0;
	newl->in_quote = NULL;
	return (newl);
}
