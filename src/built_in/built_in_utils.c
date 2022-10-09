/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:12:45 by abucia            #+#    #+#             */
/*   Updated: 2022/10/09 15:12:45 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_no_arg(t_lst_cmd **cmd, char *er_cmd, t_global *g)
{
	t_lst_parse	*tmp;

	tmp = (*cmd)->split_cmd;
	while (tmp)
	{
		if (ft_nstrncmp(tmp->str, "-", 1, 0) == 0)
		{
			g->ret = 1;
			printf("wati-minishell: %s: %s: invalid option\n", er_cmd, tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*rebuild_command(t_lst_cmd *cmd, t_global *g)
{
	t_lst_parse	*tmp;
	char		*ret;

	ret = NULL;
	tmp = cmd->split_cmd;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			if (tmp->is_near_prev == 0 && ret != NULL)
				ret = ft_strjoin(ret, " ", g);
			if (tmp->env_var_str != NULL)
				ret = ft_strjoin(ret, tmp->env_var_str, g);
			else if (tmp->str)
				ret = ft_strjoin(ret, tmp->str, g);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	check_chdir(char *str, t_global *g)
{
	if (chdir(str) != EACCES)
		ft_putendl_fd(ft_strjoin(ft_strjoin("wati-minishell: cd: ", str, g), \
		": Permission denied", g), 2);
	else
		ft_putendl_fd(ft_strjoin(ft_strjoin("wati-minishell: cd: ", str, g), \
		": Not a directory", g), 2);
	g->ret = 1;
	return (g->ret);
}

int	check_file_dir(char *str, t_global *g, int mode)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
		access parent directories: No such file or directory", 2);
		g->ret = 0;
		return (0);
	}
	else if (access(ft_strjoin(ft_strjoin(pwd, "/", g), str, g), F_OK) != 0)
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin("wati-minishell: cd: ", str, g), \
		": No such file or directory", g), 2);
		g->ret = 1;
		return (1);
	}
	else if (mode == 0)
		return (check_chdir(str, g));
	return (2);
}
