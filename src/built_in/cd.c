/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wati-Theo <wati-theo@protonmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:05:57 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/25 00:05:57 by Wati-Theo        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	b_in_cd(t_global *mini_sh)
{
	if (mini_sh->cmd->exec[1] && mini_sh->cmd->exec[2])
	{
		ft_putendl_fd("wati-minishell: cd: too many arguments", 2);
		return (1);
	}
	else if (mini_sh->cmd->exec[1])
	{
		if (!chdir(mini_sh->cmd->exec[1]))
			return (0);
		else
		{
			ft_putstr_fd("wati-minishell: cd: ", 2);
			ft_putstr_fd(mini_sh->cmd->exec[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
	}
}