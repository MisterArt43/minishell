/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 02:27:02 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/03 03:48:17 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*remove_quote(char *str, t_global *g)
{
	if (str[0] == '\"' || str[0] == '\'')
		return (ft_substr(str, 1, ft_strlen(str) - 2, g));
	return (str);
}

char	*rebuild_exec(t_lst_cmd *cmd, t_global *g)
{
	t_lst_cmd	*tmp;
	char		*ret;
	int			i;

	ret = NULL;
	tmp = cmd;
	i = 0;
	while (tmp->exec[i])
	{
		if (i != 0)
		{
			if (ret == NULL)
				ret = tmp->exec[i];
			else
				ret = ft_strjoin(ft_strjoin(ret, " ", g), tmp->exec[i], g);
		}
		i++;
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

void	b_in_echo(t_global *mini_sh, t_lst_cmd **cmd)
{
	int		i;
	int		is_nl;
	char	*str;

	mini_sh->ret = 0;
	is_nl = 1;
	i = 0;
	if (!mini_sh->cmd->exec[1])
		printf("\n");
	else
	{
		str = rebuild_exec(*cmd, mini_sh);
		str = skip_echo_option(str, &i, &is_nl, mini_sh);
		if (is_nl == 1)
			printf("%s\n", str);
		else
			ft_putstr_fd(str, 1);
	}
}
