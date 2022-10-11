/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:00:24 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 19:00:24 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	sig_child_hndlr_in_cmd(const int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		if (signal == SIGINT)
		{
			write(1, "\n", 1);
			static_signal(NULL, 130);
		}
		else if (signal == SIGQUIT)
		{
			write(1, "Quit\n", 5);
			static_signal(NULL, 131);
		}
	}
	return (130);
}

int	sig_child_hndlr(const int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("\0", 1);
		write(1, "\n", 1);
		rl_redisplay();
		static_signal(NULL, 0);
	}
	return (130);
}

void	sig_ctrl_d(t_global *mini_sh)
{
	write(1, "exit\n", 5);
	ft_gc_clear(&mini_sh->gc_parsing);
	ft_lst_env_clear(&mini_sh->env);
	exit(mini_sh->ret);
}

void	static_signal(void	*ptr, int sig)
{
	static t_global	*g;

	if (ptr != NULL)
		g = ptr;
	else
		g->ret = sig;
}
