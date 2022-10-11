/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:17:48 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 22:17:48 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	spe_ec(t_lst_cmd **new_cmd, char *ret, t_global *g)
{
	if ((*new_cmd)->split_cmd == NULL && *ret != 0)
		ft_lst_parse_add_back(&(*new_cmd)->split_cmd, \
		ft_lst_parse_new(&g->gc_parsing, ft_strjoin("\"", \
		ft_strjoin(ret, "\"", g), g), g));
}

void	lst_magic(t_lst_parse **lst, t_lst_cmd **new_cmd)
{
	(*new_cmd)->split_cmd->is_near_prev = (*lst)->is_near_prev;
	(*new_cmd)->split_cmd->prev = (*lst)->prev;
	if ((*lst)->prev)
		(*lst)->prev->next = (*new_cmd)->split_cmd;
	else
		(*new_cmd)->fd[0] = 2;
	if ((*lst)->next)
		(*lst)->next->prev = ft_lst_parse_last((*new_cmd)->split_cmd);
	ft_lst_parse_last((*new_cmd)->split_cmd)->next = (*lst)->next;
	(*lst)->next = (*new_cmd)->split_cmd;
	*lst = (*new_cmd)->split_cmd;
}
