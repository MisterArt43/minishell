/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:15:55 by abucia            #+#    #+#             */
/*   Updated: 2022/08/30 16:15:55 by abucia           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../../includes/readline-8.1/readline.h"
# include "../../includes/readline-8.1/history.h"

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <limits.h> // For cd and pwd to get PATH_MAX

/**
 * @brief gabadge memory collection
 * \struct
 * < ---- GARBADGE COLLECTOR ---- >
 */
typedef struct s_gc
{
	void		*src;
	struct s_gc	*next;
}	t_gc;

// < ---- CHAINED LIST ENVIRONEMENT ---- >
typedef struct s_lst_env
{
	char				*key;
	char				*value;
	struct s_lst_env	*next;
	struct s_lst_env	*prev;
}	t_lst_env;

typedef struct s_lst_parsed
{
	char				*env_var_str;
	char				*str;
	char				type;
	struct s_lst_parsed	*next;
	struct s_lst_parsed	*prev;
}	t_lst_parse;

/**
 * @brief chained list for all command parsed passed in the prompt
 * \struct
 * < ---- CHAINED LIST COMMAND ---- >
 */
typedef struct s_lst_cmd
{
	char				*command; //ls -a >> r.txt
	struct s_lst_parsed	*split_cmd;
	char				**exec; //ls -a
	//STDIN_FILENO -> fd_out = write && fd_in = read
	int					fd_in;
	int					fd_out;
	struct s_lst_cmd	*next;
}	t_lst_cmd;

/**
 * @brief global struct that contain the answer
 * \struct
 * < ---- GLOBAL STRUCT ---- >
 */
typedef struct s_global
{
	char	*line;
	int		**pid;
	t_gc	*gc_parsing;
	t_lst_cmd	*cmd;
	t_lst_env	*env;
	int			ret;
} t_global;

//  ------------------------------------------------
//  < ------------ GARBADGE COLLECTOR ------------ >
//  ------------------------------------------------

//create a new gc chain
t_gc	*ft_gc_new(void *var, const char *er, t_global *g);
//link a new gc chain to the list (S.O.L.)
void	*ft_gc_add_front(t_gc **alst, t_gc *new);
//link a new gc chain to the list or create the list if NULL (E.O.L.)
void	*ft_gc_add_back(t_gc **alst, t_gc *new);
//return the last chain of the list
t_gc	*ft_gc_last(t_gc *lst);
//free the current chain and the pointer inside
void	ft_gc_delone(t_gc *lst);
//free the whole list and their pointers
void	ft_gc_clear(t_gc **lst);

int	ft_gc_size(t_gc *lst);



//  ------------------------------------------------
//  < ------------        UTILS       ------------ >
//  ------------------------------------------------

//take a part of a string
char	*ft_substr(char const *s, unsigned int start, size_t len, t_global *g);
//give the lenght of the string
size_t	ft_strlen(const char *str);
//allocate the string passed in parameter
char	*ft_strdup(const char *s1, t_global *g);

int	ft_isalnum(int c);

char	*ft_strjoin(char *s1, char *s2, t_global *g);

int	ft_nstrncmp(const char *s1, const char *s2, size_t n, size_t i);

void	ft_putstr_fd(char	*s, int fd);

int	ft_isdigit(int c);

int	ft_atoi(const char *str);

void	ft_putendl_fd(char	*s, int fd);

int	ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_split(char const *s, char c);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

void	*ft_calloc(size_t count, size_t size);

//  ------------------------------------------------
//  < ------------      CHECKER       ------------ >
//  ------------------------------------------------

//check if the cmd is filled with nothing more than space, skip line, tab ...
int checker_isempty(char *cmd);
//check if the cmd have a correct format of pipe
int	check_pipe(char *cmd);
//check if the redirection are valid
int	check_redirection(char *cmd, int i, int state);




//  ------------------------------------------------
//  < ------------    CHAINED LIST    ------------ >
//  ------------------------------------------------

t_lst_cmd	*ft_lst_cmd_new(t_gc **cmd_gc, char *cmd, t_global *g);
t_lst_cmd	*ft_lst_cmd_last(t_lst_cmd *lst);
void		ft_lst_cmd_add_back(t_lst_cmd **alst, t_lst_cmd *new);
int			ft_lst_cmd_size(t_lst_cmd *lst);

t_lst_parse	*ft_lst_parse_new(t_gc **cmd_gc, char *cmd, t_global *g);
t_lst_parse	*ft_lst_parse_last(t_lst_parse *lst);
void		ft_lst_parse_add_back(t_lst_parse **alst, t_lst_parse *new);
int			ft_lst_parse_size(t_lst_parse *lst);
void		ft_lst_env_clear(t_lst_env **lst);

t_lst_env	*ft_lst_env_new(char **key, char **value);
t_lst_env	*ft_lst_env_last(t_lst_env *lst);
void		ft_lst_env_add_back(t_lst_env **alst, t_lst_env *new);


//  ------------------------------------------------
//  < ------------   PARSING COMMAND  ------------ >
//  ------------------------------------------------

void		ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh);
void		skip_to_next_word(char *str, int *i);
void		define_cmd(t_global *mini_sh);




//  ------------------------------------------------
//  < ------------      READLINE      ------------ >
//  ------------------------------------------------

void	main_mini_sh(t_global *mini_sh);

//  ------------------------------------------------
//  < ------------      BUILT-IN      ------------ >
//  ------------------------------------------------

//sort to see if it's a built in and execute it
void	sort_build_in(t_lst_cmd **cmd, t_global *mini_sh);
void	b_in_exit(t_global *mini_sh);
int		b_in_pwd(t_global *mini_sh);
int		b_in_cd(t_global *mini_sh);
int		b_in_echo(t_global *mini_sh);
int		b_in_env(t_global *mini_sh);

//  ------------------------------------------------
//  < ------------      EXEC          ------------ >
//  ------------------------------------------------
void    exec_cmd(t_global *mini_sh);
void	exec_built_in(t_global *mini_sh);

//ERROR MANAGER
int print_er(const char *er);

// tu connais
void print_env(t_lst_env *env);
char	*get_binary(t_global *mini_sh);
char	*get_path(t_global *mini_sh);

#endif
