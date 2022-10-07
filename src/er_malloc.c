/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   er_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:05:09 by abucia            #+#    #+#             */
/*   Updated: 2022/09/30 21:05:09 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	malloc_exit(t_global *g, const char *er)
{
	write(2, er, ft_strlen(er));
	write(2, "\n", 1);
	ft_gc_clear(&g->gc_parsing);
	ft_lst_env_clear(&g->env);
	exit(1);
}
