/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wati-Theo <wati-theo@protonmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:08:33 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/28 01:08:33 by Wati-Theo        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*get_path(t_global *mini_sh)
{
	while(mini_sh->env && ft_strncmp(mini_sh->env->key, "PATH", -1))
		mini_sh->env = mini_sh->env->next;
	return (mini_sh->env->value);
}

char	*get_binary(t_global *mini_sh)
{
	char	*path;
	char	**path_splited;
	char	*bin;
	int		i;

	path = get_path(mini_sh);
	path_splited = ft_split(path, ':');
	bin = NULL;
	i = 0;
	while (path_splited[i])
	{
		bin = ft_calloc(sizeof(char), ft_strlen(path_splited[i]) + ft_strlen(mini_sh->cmd->exec[0]) + 2);
		ft_strlcat(bin, path_splited[i], -1);
		ft_strlcat(bin, "/", -1);
		ft_strlcat(bin, mini_sh->cmd->exec[0], -1);
		if (access(bin, F_OK) == 0)
		{
			printf("%s\n", bin);
			return (bin);
		}
		free(bin);
		bin = NULL;
		i++;
	} 
	return (NULL);
}

void	exec_binary_no_fork(t_global *mini_sh)
{
	execve(get_binary(mini_sh), mini_sh->cmd->exec, NULL);
}
