/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:03:23 by abucia            #+#    #+#             */
/*   Updated: 2022/10/10 16:03:23 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	exec_len(t_lst_parse *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (tmp->is_near_prev == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	add_exec2(t_lst_parse **parse, t_global *g, char **ret)
{
	if (*ret == NULL)
	{
		if ((*parse)->env_var_str != NULL)
			*ret = remove_quote((*parse)->env_var_str, g);
		else
			*ret = remove_quote((*parse)->str, g);
	}
	else
	{
		if ((*parse)->env_var_str != NULL)
			*ret = ft_strjoin(*ret, remove_quote(\
			(*parse)->env_var_str, g), g);
		else
			*ret = ft_strjoin(*ret, remove_quote((*parse)->str, g), g);
	}
}

char	*add_exec(t_lst_parse **parse, t_global *g)
{
	char	*ret;

	ret = NULL;
	while ((*parse))
	{
		if ((*parse)->type == 0 || (*parse)->type == 1)
			add_exec2(parse, g, &ret);
		if ((*parse)->next && (*parse)->next->is_near_prev == 0)
			break ;
		(*parse) = (*parse)->next;
	}
	return (ret);
}

void	define_exec(t_lst_cmd **lst, t_global *g, int i)
{
	t_lst_parse	*parse;

	(*lst)->exec = ft_gc_add_back(&g->gc_parsing, ft_gc_new(\
	malloc(sizeof(char *) * (exec_len((*lst)->split_cmd) + 1)), \
	"invalide malloc in define exec", g));
	(*lst)->exec[0] = NULL;
	(*lst)->exec[exec_len((*lst)->split_cmd)] = NULL;
	i = 0;
	parse = (*lst)->split_cmd;
	while (parse)
	{
		(*lst)->exec[i] = add_exec(&parse, g);
		i++;
		if ((*lst)->exec[i - 1] == NULL || parse == NULL)
			break ;
		parse = parse->next;
	}
	(*lst)->exec[i] = NULL;
}

int	check_redirect_has_fd(t_lst_cmd *cmd)
{
	t_lst_parse	*tmp;

	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type > 2)
			if (tmp->next == NULL || tmp->next->type != 2)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
