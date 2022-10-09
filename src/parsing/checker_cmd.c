/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:55:26 by abucia            #+#    #+#             */
/*   Updated: 2022/09/09 01:55:26 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_char_isempty(char c)
{
	if (c == 0)
		return (0);
	if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
		return (1);
	return (0);
}

int	check_isempty(char *cmd)
{
	int	i;

	if (cmd[0] == 0)
		return (0);
	i = 0;
	while (cmd[i])
	{
		if (check_char_isempty(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe(char *cmd, int i, int state)
{
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			if (state == 1)
				return (0);
			else
				state = 1;
		}
		else if (state == 1)
		{
			skip_to_next_word(cmd, &i);
			if (cmd[i] != 0)
				state = 0;
		}
		if (cmd[i] != 0)
			i++;
	}
	if (state == 1)
		return (0);
	return (1);
}

int	check_redirect2(char *cmd, int *i, int *state)
{
	if (*state == 1)
		return (1);
	else if (cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '>')
			*i += 1;
		*state = 1;
		return (0);
	}
	else if (cmd[*i] == '<')
	{
		if (cmd[*i + 1] == '<')
			*i += 1;
		*state = 1;
		return (0);
	}
	return (0);
}

int	redirect_erno(char *cmd, int i)
{
	if (cmd[i] == '>')
	{
		if (cmd[i + 1] == '>')
			return (print_er(\
			"wati-minishell: syntax error near unexpected token `>>'\n"));
		return (print_er(\
		"wati-minishell: syntax error near unexpected token `>'\n"));
	}
	else if (cmd[i] == '<')
	{
		if (cmd[i + 1] == '<')
			return (print_er(\
			"wati-minishell: syntax error near unexpected token `<<'\n"));
		return (print_er(\
		"wati-minishell: syntax error near unexpected token `<'\n"));
	}
	return (0);
}

int	check_redirection(char *cmd, int i, int state)
{
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			skip_quote(cmd, &i);
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (check_redirect2(cmd, &i, &state))
				return (redirect_erno(cmd, i));
		}
		else if (check_char_isempty(cmd[i]))
			state = 0;
		if (cmd[i] != 0)
			i++;
	}
	if (state == 1)
		return (redirect_erno(cmd, i));
	return (1);
}
