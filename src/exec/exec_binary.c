/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:08:33 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/05 01:07:31 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*get_path(t_global *mini_sh)
{
	t_lst_env *cpy;

	cpy = mini_sh->env;
	while(cpy && ft_strncmp(cpy->key, "PATH", -1))
		cpy = cpy->next;
	if (cpy)
		return(cpy->value);
	return (NULL);
}

int	is_relative(t_global *mini_sh, t_lst_cmd *cmd)
{
	if ((cmd->exec[0][0] == '.' || cmd->exec[0][0] == '/'))
	{
		if (access(cmd->exec[0], X_OK) == 0)
			return (1);
		else if (access(cmd->exec[0], F_OK) == 0)
		{
			ft_putstr_fd("wati-minishell: ", 2);
			ft_putstr_fd(cmd->exec[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			mini_sh->ret = 126;
			exit(126);
		}
		else
		{
			ft_putendl_fd(ft_strjoin(ft_strjoin("wati-minishell: ", cmd->exec[0]\
			, mini_sh), ": No such file or directory", mini_sh), 2);
			mini_sh->ret = 127;
			exit(127);
		}
	}
	return (0);
}

char	*get_binary(t_global *mini_sh, t_lst_cmd *cmd)
{
	char	*path;
	char	**path_splited;
	char	*bin;
	int		i;

	if (is_relative(mini_sh, cmd) && access(cmd->exec[0], X_OK) == 0)
		return (cmd->exec[0]);
	path = get_path(mini_sh);
	path_splited = ft_split(path, ':', mini_sh);
	bin = NULL;
	i = 0;
	while (path_splited[i])
	{
		if (access(ft_strjoin(ft_strjoin(path_splited[i], "/", mini_sh), cmd->exec[0], mini_sh), F_OK) == 0)
			return (ft_strjoin(ft_strjoin(path_splited[i], "/", mini_sh), cmd->exec[0], mini_sh));
		i++;
	}
	return (NULL);
}
