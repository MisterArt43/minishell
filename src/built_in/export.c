/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:04:43 by abucia            #+#    #+#             */
/*   Updated: 2022/10/01 22:20:36 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_no_arg(t_lst_cmd **cmd, char *er_cmd, t_global *g)
{
	t_lst_parse *tmp;

	tmp = (*cmd)->split_cmd;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->str, "-", 1, 0) == 0)
		{
			g->ret = 1;
			printf("wati-minishell: %s: %s: invalid option\n",er_cmd, tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void print_export(t_lst_env *env)
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

int	skip_key(char *str, int *i)
{
	int first;

	first = 0;
	while (str[*i])
	{
		if (str[*i] == '\"')
		{
			*i += 1;
			skip_to_next_word(str, i);
			if (str[*i] == '\"')
				return (-1); //pas de key dans cette chaine
		}
		if (str[*i] == 0)
			return (0);
		if (first == 0)
		{
			if (is_valid_key_char(str[*i], 0) == 0)
				return (0);
			first = 1;
		}
		else
		{
			if (check_char_isempty(str[*i]) == 0)
				return (1);
			if (str[*i] == '=')
				return (1);
			if (is_valid_key_char(str[*i], 1) == 0)
				return (0);
		}
		*i += 1;
	}
	return (1);
}

char	*skip_value(char *str, int *i, t_global *g)
{
	char *ret;
	int	start;

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
			else if (str[*i + 1] == '\"' || str[*i + 1] == '\'')
				*i += 2;
			else
			{
				skip_quote(str, i);
				ret = ft_strjoin(ret, ft_substr(str, start + 1, *i - start - 2, g), g);
			}
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

	tmp = *env;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->key, key, ft_strlen(key), 0) == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		free(key);
		free(tmp->value);
		tmp->value = value;
	}
	else
		ft_lst_env_add_back(env, ft_lst_env_new(&key, &value));
}

void	sort_export(t_global *g, int *i, char *str, int start)
{
	char		*key;
	char		*value;
	int			ret;

	ret = skip_key(str, i);
	if (ret == 1 && (str[start] == '\'' || str[start] == '\"'))
	{
		if (str[*i - start] == '\'' || str[*i - start] == '\"')
			key = ft_substr(str, start + 1, *i - start - 2, NULL);
		else
			ret = 0;
	}
	else if (ret == 1)
		key = ft_substr(str, start, *i - start, NULL);
	if (ret == 1)
	{
		value = NULL;
		if (!key)
		{
			malloc_exit(g, "malloc error: env key");
		}
		if (str[*i] == '=')
		{
			value = skip_value(str, i ,g);
			if (value == NULL)
			{
				free(key);
				malloc_exit(g, "malloc error: env value");
			}
		}
		export_put_value(key, value, g, &g->env);
	}
	if (ret == 0)
	{
		g->ret = 1;
		while (check_char_isempty(str[*i]) == 1)
			*i += 1;
		print_er("bash: export: `");
		print_er(str);
		print_er("': not a valid identifier\n");
		//printf invalid key error;
	}
}

//faire attention au redirection et fichier a ignorer
int	exec_export(t_lst_cmd *cmd, t_global *mini_sh, char *str)
{
	int	i;
	char *key;
	char *value;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		skip_to_next_word(str, &i);
		sort_export(mini_sh, &i, str, i);
		printf("%c / %d\n", str[i], i);
	}
	return (1);
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
			if (ret == NULL)
			{
				if (tmp->env_var_str != NULL)
					ret = tmp->env_var_str;
				else
					ret = tmp->str;
			}
			else 
			{
				if (tmp->is_near_prev == 0)
					ret = ft_strjoin(ret, " ", g);
				if (tmp->env_var_str != NULL)
					ret = ft_strjoin(ret, tmp->env_var_str, g);
				else if (tmp->str)	
					ret = ft_strjoin(ret, tmp->str, g);
			}
		}
		tmp = tmp->next;
	}
	//printf("###################\n%s\n", ret);
	return (ret);
}

int	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{
	t_lst_parse	*tmp;
	char *line;

	mini_sh->ret = 0;
	tmp = (*cmd)->split_cmd;
	if (ft_strstrlen((*cmd)->exec) > 1)
	{
		//si ya un pipe c'est inutile
		if (ft_lst_cmd_size(*cmd) != 1)
			return (1);
		if (check_no_arg(cmd, "export", mini_sh) == 0) // pas d'option "-..."
			return (0);
		line = rebuild_command(*cmd, mini_sh);
		return (exec_export(*cmd, mini_sh, line));
	}
	else
		print_export(mini_sh->env);
	return (1);
}