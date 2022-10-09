/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:10:53 by abucia            #+#    #+#             */
/*   Updated: 2022/10/09 15:10:53 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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

void	sort_export_ret_zero(t_global *g, char *str, int *i)
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
		sort_export_ret_zero(g, str, i);
}

void	exec_export(t_global *mini_sh, char *str)
{
	int	i;

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
