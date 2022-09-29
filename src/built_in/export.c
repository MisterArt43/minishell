/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:04:43 by abucia            #+#    #+#             */
/*   Updated: 2022/09/20 03:04:43 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_no_arg(t_lst_cmd **cmd)
{
	t_lst_parse *tmp;

	tmp = (*cmd)->split_cmd;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->str, "-", 1, 0))
		{
			printf("bash: export: %s: invalid option\n", tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_valid_key(char *str)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while(str[i])
	{
		if (checker_char_isempty(str[i]) != 0 && str[i] != '=')
			state = 1;
		if (str[i] == '=')
		{
			if (i == 0 || (state == 0 && (str[0] == '\"' || str[0] == '\'')))
			{
				printf("bash: export: `=': not a valid identifier");
				return (0);
			}
			else if (str[i + 1] == 0)
				return (2);
			else
				return (1);
		}
		else if (!ft_isalnum(str[i]))
			if (!(i == 0 && (str[i] == '\"' || str[i] == '\'')))
				return (0);
		i++;
	}
	return (3);
}

char	*get_key(char *str, int *i)
{
	char	*key;
	int		start;

	start = *i;
	if (str[0] == '\'' || str[0] == '\"')
		start++;
	if (str[start] == '=')
	{
		printf("bash: export: `=': not a valid identifier\n");
		return (NULL);
	}
	while (str[*i])
	{
		if (ft_isalnum(str[*i]) == 0 && str[*i] != '_')
			return (NULL);
		if (str[*i] == '=')
			return (ft_substr(str,start, ft_strlen(str), NULL));
		*i += 1;
	}
	
}

void print_env(t_lst_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

//faire attention au redirection et fichier a ignorer
void	exec_export(t_lst_cmd *cmd, t_global *mini_sh)
{
	int	i;
	int	j;
	char *key;
	char *value;

	while (cmd->exec[i])
	{
		i = 0;
		
		
		if ()
		{
			key = get_key(cmd->exec[i], &i);
			value = get_value("",mini_sh);
			if (key == NULL)
				break ;
			ft_lst_env_add_back(&mini_sh->env, ft_lst_env_new());
		}
		i++;
	}
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
					ft_gc_add_back(&g->gc_parsing, ft_gc_new(ft_strjoin(ret, \
					" ", g), "error while malloc in export", g));
				if (tmp->env_var_str != NULL)
					ft_gc_add_back(&g->gc_parsing, ft_gc_new(ft_strjoin(ret, \
					tmp->env_var_str, g), "error while malloc in export", g));
				else
					ft_gc_add_back(&g->gc_parsing, ft_gc_new(ft_strjoin(ret, \
					tmp->str, g), "error while malloc in export", g));
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{
	t_lst_parse	*tmp;
	char *line;

	tmp = (*cmd)->split_cmd;
	if (ft_strlen((*cmd)->exec) > 1)
	{
		//si ya un pipe c'est inutile
		if (ft_lst_cmd_size(*cmd) != 1)
			return (1);
		if (check_no_arg(cmd) == 0) // pas d'option "-..."
			return (0);
		line = rebuild_command(*cmd, mini_sh);
		exec_export(tmp, mini_sh);
	}
	else
		print_env(mini_sh->env);
}