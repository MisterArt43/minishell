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
void	define_parse(t_lst_parse **lst, int i, int init, t_lst_parse *tmp)
{
	while (tmp)
	{
		if (ft_strlen(tmp->str) == 2 && \
		tmp->str[0] == '>' && tmp->str[1] == '>')
			tmp->type = 3;
		else if (ft_strlen(tmp->str) == 1 && tmp->str[0] == '>')
			tmp->type = 4;
		else if (ft_strlen(tmp->str) == 2 && \
		tmp->str[0] == '<' && tmp->str[1] == '<')
			tmp->type = 5;
		else if (ft_strlen(tmp->str) == 1 && tmp->str[0] == '<')
			tmp->type = 6;
		else if (tmp->prev != NULL && tmp->prev->type > 2)
			tmp->type = 2;
		else if (init == 0)
		{
			tmp->type = 0;
			init = 1;
		}
		else
			tmp->type = 1;
		i++;
		tmp = tmp->next;
	}
}

int	check_no_cmd(t_lst_cmd *cmd)
{
	t_lst_parse	*tmp;

	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

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

char	*add_exec(t_lst_parse **parse, t_lst_cmd **lst, t_global *g)
{
	char	*ret;

	ret = NULL;
	while ((*parse))
	{
		if ((*parse)->type == 0 || (*parse)->type == 1)
		{
			if ((*parse)->env_var_str != NULL)
				ret = ft_strjoin(ret, remove_quote(\
				(*parse)->env_var_str, g), g);
			else
				ret = ft_strjoin(ret, remove_quote((*parse)->str, g), g);
		}
		if ((*parse)->next && (*parse)->next->is_near_prev == 0)
			break ;
		(*parse) = (*parse)->next;
	}
	return (ret);
}

int	define_exec(t_lst_cmd **lst, t_global *g, int i)
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
		(*lst)->exec[i++] = add_exec(&parse, lst, g);
		if ((*lst)->exec[i - 1] == NULL || parse == NULL)
			break ;
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
				parse->heredoc = ft_heredoc(\
				remove_quote(parse->next->str, g), g);
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
		define_parse(&tmp_cmd->split_cmd, 0, 0, tmp_cmd->split_cmd);
		if (check_no_cmd(tmp_cmd) == 0)
		{
			tmp_cmd->exec = ft_gc_add_back(&mini_sh->gc_parsing, ft_gc_new(\
			malloc(sizeof(char *)), \
			"error malloc while creating exec", mini_sh));
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
