/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:04:43 by abucia            #+#    #+#             */
/*   Updated: 2022/10/05 03:08:42 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_valid_key_char(char c, char mode)
{
	if (mode == 0)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			return (1);
		return (0);
	}
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	skip_key(char *str, int *i, int first, int mode)
{
	while (str[*i])
	{
		if (str[*i] == '\"')
		{
			*i += 1;
			skip_to_next_word(str, i);
			if (str[*i] == '\"')
				return (-1);
		}
		if (str[*i] == 0 || (first == 0 && is_valid_key_char(str[*i], 0) == 0))
			return (0);
		if (first == 0)
			first = 1;
		else if (check_char_isempty(str[*i]) == 0 \
		|| (str[*i] == '=' && mode == 1))
			return (1);
		else if (is_valid_key_char(str[*i], 1) == 0)
			return (0);
		*i += 1;
	}
	return (1);
}

char	*skip_value(char *str, int *i, t_global *g)
{
	char	*ret;
	int		start;

	ret = ft_strdup("", g);
	*i += 1;
	while (1)
	{
		start = *i;
		if (str[*i] == 0 || check_char_isempty(str[*i]) == 0)
			return (ft_strdup(ret, NULL));
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (str[*i + 1] == 0)
				return (ft_strdup(ret, NULL));
			skip_quote(str, i);
			ret = ft_strjoin(ret, \
			ft_substr(str, start + 1, *i - start - 2, g), g);
		}
		else
		{
			skip_word(str, i);
			ret = ft_strjoin(ret, ft_substr(str, start, *i - start, g), g);
		}
	}
	return (ft_strdup(ret, NULL));
}

void	export_put_value(char *key, char *value, t_global *g, t_lst_env **env)
{
	t_lst_env	*tmp;

	if (ft_nstrncmp(key, "_", 2, 0) != 0)
	{
		tmp = *env;
		while (tmp)
		{
			if (ft_nstrncmp(tmp->key, key, ft_strlen(key), 0) == 0)
				break ;
			tmp = tmp->next;
		}
		if (tmp != NULL)
		{
			if (key != NULL)
			{
				free(key);
				free(tmp->value);
				tmp->value = value;
			}
		}
		else
			ft_lst_env_add_back(env, ft_lst_env_new(&key, &value), g);
	}
}

void	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{
	char	*line;

	mini_sh->ret = 0;
	if (ft_strstrlen((*cmd)->exec) > 1)
	{
		if (check_no_arg(cmd, "export", mini_sh) == 0)
		{
			mini_sh->ret = 2;
			return ;
		}
		if (ft_lst_cmd_size(*cmd) != 1)
		{
			mini_sh->ret = 0;
			return ;
		}
		line = rebuild_command(*cmd, mini_sh);
		exec_export(mini_sh, line);
		return ;
	}
	else
		print_export(mini_sh->env);
	mini_sh->ret = 1;
}
