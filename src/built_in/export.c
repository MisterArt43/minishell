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

int	check_valid_key(char *str)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while(str[i])
	{
		if (state == 0)
		{
			if (str[i] == '=')
			{
				if (i > 0)
					state = 1;
				else
					return (0);
			}
			else if (!ft_isalnum(str[i]))
				return (0);
		}
		i++;
	}
}

int	b_in_export(t_lst_cmd **cmd, t_global *mini_sh)
{

}