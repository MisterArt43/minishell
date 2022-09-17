/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 00:39:49 by abucia            #+#    #+#             */
/*   Updated: 2022/09/17 08:38:45 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	skip_to_next_word(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == ' ' \
		|| str[*i] == '\t' \
		|| str[*i] == '\n' \
		|| str[*i] == '\r')
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
		if (str[*i] == ' ' \
		|| str[*i] == '\t' \
		|| str[*i] == '\n' \
		|| str[*i] == '\r' \
		|| str[*i] == '\"' \
		|| str[*i] == '\'')
			return ;
		*i += 1;
	}
}

void	sort_split(t_lst_cmd **cmd, int *i, t_global *g, int start)
{
	skip_to_next_word((*cmd)->command, i);
	if ((*cmd)->command[*i] == '\'' || (*cmd)->command[*i] == '\"')
	{
		start = *i;
		skip_quote((*cmd)->command, i);
		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, ft_substr((*cmd)->command, start, *i - start, g), g));
		printf("Quote\n");
	}
	else if ((*cmd)->command[*i] == 0)
		return ;
	else
	{
		start = *i;
		skip_word((*cmd)->command, i);

		ft_lst_parse_add_back(&(*cmd)->split_cmd, ft_lst_parse_new(&g->gc_parsing, ft_substr((*cmd)->command, start, *i - start, g), g));
		printf("Word\n");
	}
}

t_lst_env	*cmp_env_key(int *i, char *str, t_global *g)
{
	t_lst_env	*tmp;
	int			j;
	int			tmp_i;

	if (!ft_isalnum(str[*i + 1]))
		return (NULL);
	tmp = g->env;
	while (tmp)
	{
		tmp_i = *i + 1;
		j = 0;
		//printf("key : %c | str : %c\n", tmp->key[j], str[*i + 1]);
		if (tmp->key[j] == str[*i + 1])
		{
			while (1)
			{
				//printf("they are inside\n\n");
				//printf("key : %c/%d | str : %c/%d\n", tmp->key[j],tmp->key[j] , str[tmp_i],str[tmp_i]);
				if (tmp->key[j] == 0 && ft_isalnum(str[tmp_i]) == 0)
				{
					//printf("added\n\n");
					*i = tmp_i;
					return (tmp);
				}
				if (str[tmp_i] != tmp->key[j] || !ft_isalnum(str[tmp_i]))
					break ;
				j++;
				tmp_i++;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	replace_env_var(t_lst_parse **lst, t_global *g)
{
	int	i;
	int start;
	int end;
	char *ret;
	t_lst_env	*find;

	if ((*lst)->str[0] == '\'')
		return ;
	i = 0;
	start = 0;
	ret = NULL;
	while ((*lst)->str[i])
	{
		if ((*lst)->str[i] == '$')
		{
			//printf("i need dollars ... \n");
			end = i;
			find = cmp_env_key(&i, (*lst)->str, g);
			if (find != NULL)
			{
				if (ret == NULL)
					ret = ft_strjoin(ft_substr((*lst)->str, start, end - start, g), find->value, g);
				else
					ret = ft_strjoin(ret, ft_strjoin(ft_substr((*lst)->str, start, end - start, g), find->value, g), g);
				start = i;
				i--;
				//printf("\nenv var detected : ret = '%s'\n",ret);
			}
		}
		i++;
	}
	ret = ft_strjoin(ret, ft_substr((*lst)->str, start , i - start, g), g);
	if (ret != NULL)
		printf("->env var detected : before = '%s' after = '%s'\n", (*lst)->str, ret);
	(*lst)->env_var_str = ret;
}

void	ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh)
{
	int			i;
	t_lst_parse	*lst_parse;

	i = 0;
	while ((*cmd)->command[i])
		sort_split(cmd, &i, mini_sh, 0);
	lst_parse = (*cmd)->split_cmd;
	while (lst_parse)
	{
		replace_env_var(&lst_parse, mini_sh);
		lst_parse = lst_parse->next;
	}
	
	//printf("CMD SIZE : %d\n", ft_lst_parse_size((*cmd)->split_cmd));
}