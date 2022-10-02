/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 01:06:50 by abucia            #+#    #+#             */
/*   Updated: 2022/09/08 01:06:50 by abucia           ###   ########lyon.fr   */
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

t_lst_parse	*ft_lst_parse_last(t_lst_parse *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_parse_add_back(t_lst_parse **alst, t_lst_parse *new)
{
	t_lst_parse	*tmp;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = ft_lst_parse_last(*alst);
	tmp->next = new;
	new->prev = tmp;
}

int	ft_lst_parse_size(t_lst_parse *lst)
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

//------------------------------------------------------------
//env

t_lst_env	*ft_lst_env_new(char **key, char **value)
{
	t_lst_env	*newl;

	newl = malloc(sizeof(t_lst_env));;
	if (!newl)
		return (NULL);
	newl->key = *key;
	if (!value)
		newl->value = NULL;
	newl->value = *value;
	newl->prev = NULL;
	newl->next = NULL;
	return (newl);
}

t_lst_env	*ft_lst_env_last(t_lst_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_env_add_back(t_lst_env **alst, t_lst_env *new)
{
	t_lst_env	*tmp;

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

void	ft_lst_env_del_in(t_lst_env *lst)
{
	if (lst->prev != NULL)
	{
		if (lst->next != NULL)
			lst->prev->next = lst->next;
		else
			lst->prev->next = NULL;
	}
	else
		if (lst->next != NULL)
			lst->next->prev = NULL;
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