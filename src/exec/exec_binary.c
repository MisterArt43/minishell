/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:08:33 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/09/30 17:23:18 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*get_path(t_global *mini_sh)
{
	t_lst_env *cpy;

	cpy = mini_sh->env;
	while(cpy && ft_strncmp(cpy->key, "PATH", -1))
		cpy = cpy->next;
	return(cpy->value);
}

char	*get_binary(t_global *mini_sh, t_lst_cmd *cmd)
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
		ft_strlcat(bin, cmd->exec[0], -1);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		bin = NULL;
		i++;
	}
	return (NULL);
}
