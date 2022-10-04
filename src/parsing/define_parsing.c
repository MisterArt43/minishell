/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:27:48 by abucia            #+#    #+#             */
/*   Updated: 2022/09/14 19:27:48 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/**
 * 0:command
 * 1:param
 * 2:fd || heredoc_word
 * 3-6:redirect
 * @param lst
 */
void	define_parse(t_lst_parse **lst)
{
	t_lst_parse	*tmp_cmd;
	int			i;
	int			init;

	init = 0;
	i = 0;
	tmp_cmd = *lst;
	while(tmp_cmd)
	{
		if (ft_strlen(tmp_cmd->str) == 2 && tmp_cmd->str[0] == '>' && tmp_cmd->str[1] == '>')
			tmp_cmd->type = 3;
		else if (ft_strlen(tmp_cmd->str) == 1 && tmp_cmd->str[0] == '>')
			tmp_cmd->type = 4;
		else if (ft_strlen(tmp_cmd->str) == 2 && tmp_cmd->str[0] == '<' && tmp_cmd->str[1] == '<')
			tmp_cmd->type = 5;
		else if (ft_strlen(tmp_cmd->str) == 1 && tmp_cmd->str[0] == '<')
			tmp_cmd->type = 6;
		else if (tmp_cmd->prev != NULL && tmp_cmd->prev->type > 2)
			tmp_cmd->type = 2;
		else if (init == 0)
		{
			tmp_cmd->type = 0;
			init = 1;
		}
		else
			tmp_cmd->type = 1;
		i++;
		tmp_cmd = tmp_cmd->next;
	}
}

int	check_no_cmd(t_lst_cmd *cmd)
{
	t_lst_parse *tmp;

	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	define_exec(t_lst_cmd **lst, t_global *g, int i)
{
	t_lst_parse	*parse;

	parse = (*lst)->split_cmd;
	while (parse)
	{
		if (i == 0)
			i++;
		else if (parse->type == 1 && parse->prev->type <= 2)
			i++;
		parse = parse->next;
	}
	(*lst)->exec = ft_gc_add_back(&g->gc_parsing, ft_gc_new(malloc(sizeof(char *) * (i + 1)), "invalide malloc in define exec", g));
	(*lst)->exec[0] = NULL;
	(*lst)->exec[i] = NULL;
	i = 0;
	parse = (*lst)->split_cmd;
	while (parse)
	{
		if (i == 0 && parse->type == 0)
		{
			if (parse->env_var_str != NULL)
				(*lst)->exec[i++] = parse->env_var_str;
			else
				(*lst)->exec[i++] = parse->str;
		}
		else if (parse->type == 1)
		{
			if (parse->env_var_str != NULL)
				(*lst)->exec[i++] = parse->env_var_str;
			else
				(*lst)->exec[i++] = parse->str;
		}
		parse = parse->next;
	}
}

char	*ft_heredoc(char *c, t_global *g)
{
	char	*cmd;
	char	*res;

	res = NULL;
	while (1)
	{
		cmd = readline("heredoc> ");
		if (!cmd)
			break ;
		if (ft_strncmp(c, cmd, -1) == 0)
			break ;
		if (!res)
			res = ft_strdup(cmd, g);
		else
			res = ft_strjoin(ft_strjoin(res, "\n", g), cmd, g);
		free(cmd);
		if (!cmd)
			return (res);
	}
	res = ft_strjoin(res, "\n", g);
	free(cmd);
	return (res);
}

void	do_heredoc(t_lst_cmd *lst, t_global *g)
{
	t_lst_parse	*parse;

	parse = lst->split_cmd;
	while (parse)
	{
		if (parse->type == 5)
		{
			if (parse->next->in_quote != NULL)
				parse->heredoc = ft_heredoc(remove_quote(parse->next->str, g), g);
			else
				parse->heredoc = ft_heredoc(parse->next->str, g);
		}
		parse = parse->next;
	}
}

void	define_cmd(t_global *mini_sh)
{
	t_lst_cmd	*tmp_cmd;

	tmp_cmd = mini_sh->cmd;
	while (tmp_cmd)
	{
		define_parse(&tmp_cmd->split_cmd);
		if (check_no_cmd(tmp_cmd) == 0)
		{
			tmp_cmd->exec = ft_gc_add_back(&mini_sh->gc_parsing, ft_gc_new(\
			malloc(sizeof(char *)), "error malloc while creating exec", mini_sh));
			tmp_cmd->exec[0] = NULL;
		}
		else
			define_exec(&tmp_cmd, mini_sh, 0);
		tmp_cmd = tmp_cmd->next;
	}
	tmp_cmd = mini_sh->cmd;
	while (tmp_cmd)
	{
		do_heredoc(tmp_cmd, mini_sh);
		tmp_cmd = tmp_cmd->next;
	}
}