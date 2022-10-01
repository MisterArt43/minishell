/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:08:33 by Wati-Theo         #+#    #+#             */
/*   Updated: 2022/10/01 21:25:23 by abucia           ###   ########lyon.fr   */
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

char	*get_binary(t_global *mini_sh, t_lst_cmd *cmd)
{
	char	*path;
	char	**path_splited;
	char	*bin;
	int		i;

	path = get_path(mini_sh);
	path_splited = ft_split(path, ':', mini_sh);
	bin = NULL;
	i = 0;
	while (path_splited[i])
	{
		// bin = ft_calloc(sizeof(char), ft_strlen(path_splited[i]) + ft_strlen(cmd->exec[0]) + 2);
		// ft_strjoin(ft_strjoin(path_splited[i], "/", mini_sh), cmd->exec[0], mini_sh);
		// ft_strlcat(bin, path_splited[i], -1);
		// ft_strlcat(bin, "/", -1);
		// ft_strlcat(bin, cmd->exec[0], -1);
		if (access(ft_strjoin(ft_strjoin(path_splited[i], "/", mini_sh), cmd->exec[0], mini_sh), F_OK) == 0)
			return (ft_strjoin(ft_strjoin(path_splited[i], "/", mini_sh), cmd->exec[0], mini_sh));
		i++;
	}
	return (NULL);
}
