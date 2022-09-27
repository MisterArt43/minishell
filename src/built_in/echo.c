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

int	b_in_echo(t_global *mini_sh)
{
	int	i;
	int nl;

	nl = 1;
	if (!mini_sh->cmd->exec[1])
		printf("\n");
	else if (!ft_strncmp(mini_sh->cmd->exec[1], "-n", -1) && !mini_sh->cmd->exec[2])
		return (0);
	else
	{
		i = 1;
		if (!ft_strncmp(mini_sh->cmd->exec[1], "-n", -1))
		{
			i = 2;
			nl = 0;
		}
		while (mini_sh->cmd->exec[i])
		{
			printf("%s", mini_sh->cmd->exec[i]);
			printf(" ");
			i++;
		}
		if (nl)
			printf("\n");
	}
	return (0);
}
