/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:43:10 by abucia            #+#    #+#             */
/*   Updated: 2022/10/10 15:43:10 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	heredoc(t_lst_parse *tmp)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (ft_putendl_fd("PIPE ERR", 2));
	write(fd[1], tmp->heredoc, ft_strlen(tmp->heredoc));
	dup2(fd[0], STDIN_FILENO);
	if (fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		close(fd[0]);
}

void	left_redirect(int *fd_in, t_lst_parse *tmp, t_global *g)
{
	if (*fd_in > 1)
		close(*fd_in);
	*fd_in = open(remove_quote(tmp->next->str, g), O_RDONLY);
	dup2(*fd_in, STDIN_FILENO);
	if (*fd_in > 0)
		close(*fd_in);
}

void	right_right_redirect(int *in, int *out, t_lst_parse *tmp, t_global *g)
{
	if (*in > 1)
		close(*in);
	if (*out > 1)
		close(*out);
	*out = open(remove_quote(tmp->next->str, g), \
	O_CREAT | O_RDWR | O_APPEND, \
	S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	dup2(*out, STDOUT_FILENO);
	if (*out > 0)
		close(*out);
}

void	right_redirect(int *fd_in, int *fd_out, t_lst_parse *tmp, t_global *g)
{
	if (*fd_in > 1)
		close(*fd_in);
	if (*fd_out > 1)
		close(*fd_out);
	*fd_out = open(remove_quote(tmp->next->str, g), \
	O_CREAT | O_RDWR | O_TRUNC, \
	S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	dup2(*fd_out, STDOUT_FILENO);
	if (*fd_out > 1)
		close(*fd_out);
}

void	check_fd_in(int *fd_in, int *fd_out, t_lst_cmd *cmd, t_global *g)
{
	t_lst_parse	*tmp;

	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 4 || tmp->type == 3)
			check_fd_out(fd_in, fd_out, tmp, g);
		if (tmp->type == 6 && *fd_in != 1)
			if (!access(remove_quote(tmp->next->str, g), F_OK))
				if (check_file_dir(remove_quote(tmp->next->str, g), g, 1) == 2)
					left_redirect(fd_in, tmp, g);
		if (tmp->type == 5 && *fd_in != 1)
			heredoc(tmp);
		tmp = tmp->next;
	}
}
