/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 03:13:00 by abucia            #+#    #+#             */
/*   Updated: 2022/09/20 03:13:00 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	sort_build_in(t_lst_cmd **cmd, t_global *mini_sh)
{
	if (ft_nstrncmp((*cmd)->exec[0], "export", ft_strlen((*cmd)->exec[0]), 0))
	{
		
	}
}