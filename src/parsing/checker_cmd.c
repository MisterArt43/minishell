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

int checker_isempty(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
	{
		//printf("%c",cmd[i]);
		if (cmd[i] != ' ' || cmd[i] != '\t' || cmd[i] != '\n' || cmd[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe(char *cmd)
{
	int	i = 0;
	int	state = 0;

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