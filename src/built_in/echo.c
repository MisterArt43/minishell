/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wati-Theo <wati-theo@protonmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 02:27:02 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/27 02:27:02 by Wati-Theo        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*remove_quote(char *str, t_global *g)
{
	if (str[0] == '\"' || str[0] == '\'')
		return (ft_substr(str, 1, ft_strlen(str) -2, g));
	return (str);
}

char	*rebuild_command_without_quote(t_lst_cmd *cmd, t_global *g)
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
					ret = remove_quote(tmp->env_var_str, g);
				else
					ret = remove_quote(tmp->str, g);
			}
			else 
			{
				if (tmp->is_near_prev == 0)
					ret =ft_strjoin(ret, " ", g);
				if (tmp->env_var_str != NULL)
					ret =ft_strjoin(ret, remove_quote(tmp->env_var_str, g), g);
				else if (tmp->str)	
					ret =ft_strjoin(ret, remove_quote(tmp->str, g), g);
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}

char	*skip_echo_option(char *str, int *i, int *is_nl, t_global *g)
{
	int	start;

	start = 0;
	while (str[*i])
	{
		if (str[*i] == '-')
		{
			*i += 1;
			if (str[*i] != 'n')
				break ;
			while (str[*i] == 'n')
				*i += 1;
			if (check_char_isempty(str[*i]) != 0)
				break ;
			else
				*is_nl = 0;
			start = *i;
		}
		*i += 1;
	}
	if (*is_nl == 0)
		start++;
	return (ft_substr(str, start, ft_strlen(str), g));
}

int	b_in_echo(t_global *mini_sh, t_lst_cmd **cmd)
{
	int		i;
	int		is_nl;
	char	*str;

	is_nl = 1;
	i = 0;
	if (!mini_sh->cmd->exec[1])
		printf("\n");
	else
	{
		str = rebuild_command_without_quote(*cmd, mini_sh);
		str = skip_echo_option(str, &i, &is_nl, mini_sh);
		if (is_nl == 1)
			printf("%s\n", str);
		else
			ft_putstr_fd(str, 1);
	}
}
