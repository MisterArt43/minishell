/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:31:19 by tschlege          #+#    #+#             */
/*   Updated: 2022/10/01 23:42:13 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_path(t_global *mini_sh, t_lst_cmd *cmd)
{
	if (!get_path(mini_sh) || !ft_strncmp(get_path(mini_sh), "NULL", -1))
		{
			ft_putstr_fd("wati-minishell: ", 2);
			ft_putstr_fd(cmd->exec[0], 2);
			ft_putendl_fd(": command not found", 2);
			mini_sh->ret = 127;
			return (1);
		}
	else
		return (0);
}