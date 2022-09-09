/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:39:49 by abucia            #+#    #+#             */
/*   Updated: 2022/09/10 00:08:28 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	skip_to_next_word(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\r')
			*i += 1;
		else
			return ;
	}
}

void	skip_quote(char *str, int *i)
{
	char	c;

	c = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != c)
		*i += 1;
	if (str[*i] == c)
		*i += 1;
}

void	skip_word(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\"' || str[*i] == '\'')
			return ;
		*i += 1;
	}
}

void	sort_split(t_lst_cmd **cmd, int *i, t_global *g)
{
	int j;

	j = 0;
	if ((*cmd)->command[*i] == ' ' || (*cmd)->command[*i] == '\t' || (*cmd)->command[*i] == '\n' || (*cmd)->command[*i] == '\r')
		skip_to_next_word((*cmd)->command, i);
	else if ((*cmd)->command[*i] == '\'' || (*cmd)->command[*i] == '\"')
	{
		j = *i;
		skip_quote((*cmd)->command, i);
		
	}
	else if ((*cmd)->command[*i] == 0)
		return ;
	else
	{
		j = *i;
		skip_word((*cmd)->command, i);
		*count += 1;
	}
}

//  ls -a -R -L "ts ' 'ts"'haha' = 6
unsigned int	splitlen(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;

	while (str[i])
		sort_split(str, &count, &i);
	return (count);
}

void	ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh)
{
	//t_lst_parse	*res;
	//res = ft_gc_add_back(&mini_sh->gc_parsing, ft_gc_new(malloc(sizeof(t_lst_parse)), "Error occur while mallocing"));
	int		i;

	i = 0;
	while ((*cmd)->command[i])
	{
		sort_split(cmd, &i, mini_sh);
	}


	//printf("nb to parse in this cmd : %u\n", splitlen(str));
	//res = malloc(sizeof(char *) * (splitlen(str) + 1));
	return (res);
}