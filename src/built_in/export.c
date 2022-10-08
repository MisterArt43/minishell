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

int	check_no_arg(t_lst_cmd **cmd, char *er_cmd, t_global *g)
{
	t_lst_parse	*tmp;

	tmp = (*cmd)->split_cmd;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->str, "-", 1, 0) == 0)
		{
			g->ret = 1;
			printf("wati-minishell: %s: %s: invalid option\n", er_cmd, tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_export(t_lst_env *env)
{
	while (env)
	{
		if (env->value == NULL)
			printf("delare - x %s\n", env->key);
		else
			printf("declare - x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

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

int	skip_key(char *str, int *i, int first)
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
		else if (check_char_isempty(str[*i]) == 0 || str[*i] == '=')
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
			free(key);
			free(tmp->value);
			tmp->value = value;
		}
		else
			ft_lst_env_add_back(env, ft_lst_env_new(&key, &value), g);
	}
}

void	sort_export_ret_one(t_global *g, char *str, int *i, t_lst_env *tmp)
{
	if (!tmp->key)
		malloc_exit(g, "malloc error: env key");
	if (str[*i] == '=')
	{
		tmp->value = skip_value(str, i, g);
		if (tmp->value == NULL)
		{
			free(tmp->key);
			malloc_exit(g, "malloc error: env value");
		}
	}
	export_put_value(tmp->key, tmp->value, g, &g->env);
}

void	sort_export_ret_zero(t_global *g, int ret, char *str, int *i)
{
	g->ret = 1;
	while (check_char_isempty(str[*i]) == 1)
		*i += 1;
	print_er("wati-minishell: export: `");
	print_er(str);
	print_er("': not a valid identifier\n");
}

void	sort_export(t_global *g, int *i, char *str, int start)
{
	t_lst_env	tmp;
	int			ret;

	ret = skip_key(str, i, 0);
	tmp.value = NULL;
	if (ret == 1 && (str[start] == '\'' || str[start] == '\"'))
	{
		if (str[*i - start] == '\'' || str[*i - start] == '\"')
			tmp.key = ft_substr(str, start + 1, *i - start - 2, NULL);
		else
			ret = 0;
	}
	else if (ret == 1)
		tmp.key = ft_substr(str, start, *i - start, NULL);
	if (ret == 1)
		sort_export_ret_one(g, str, i, &tmp);
	if (ret == 0)
		sort_export_ret_zero(g, ret, str, i);
}

void	exec_export(t_lst_cmd *cmd, t_global *mini_sh, char *str)
{
	int		i;
	char	*key;
	char	*value;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		skip_to_next_word(str, &i);
		sort_export(mini_sh, &i, str, i);
	}
	mini_sh->ret = 1;
}

char	*rebuild_command(t_lst_cmd *cmd, t_global *g)
{
	t_lst_parse	*tmp;
	char		*ret;

	ret = NULL;
	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			if (tmp->is_near_prev == 0 && ret != NULL)
				ret = ft_strjoin(ret, " ", g);
			if (tmp->env_var_str != NULL)
				ret = ft_strjoin(ret, tmp->env_var_str, g);
			else if (tmp->str)
				ret = ft_strjoin(ret, tmp->str, g);
		}
		tmp = tmp->next;
	}
	return (ret);
}

void	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{
	t_lst_parse	*tmp;
	char		*line;

	mini_sh->ret = 0;
	tmp = (*cmd)->split_cmd;
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
		exec_export(*cmd, mini_sh, line);
		return ;
	}
	else
		print_export(mini_sh->env);
	mini_sh->ret = 1;
}
