/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:13:56 by tschlege          #+#    #+#             */
/*   Updated: 2022/10/11 19:15:46 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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

	newl = malloc(sizeof(t_lst_env));
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
