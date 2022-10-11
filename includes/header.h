/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:15:55 by abucia            #+#    #+#             */
/*   Updated: 2022/10/11 21:03:12 by tschlege         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <termios.h>

# include <limits.h> // For cd and pwd to get PATH_MAX

# define CD_ERROR_LOST "cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory"
# define FORK_OVERRIDE "wati-minishell: fork: Resource temporarily unavailable"
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
	char				is_near_prev;
	char				*in_quote;
	char				type;
	char				*heredoc;
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
	char				*command;
	struct s_lst_parsed	*split_cmd;
	char				**exec;
	int					fd[2];
	struct s_lst_cmd	*next;
}	t_lst_cmd;

/**
 * @brief global struct that contain the answer
 * \struct
 * < ---- GLOBAL STRUCT ---- >
 */
typedef struct s_global
{
	int			in_cmd;
	int			ret;
	char		*line;
	int			**pid;
	t_gc		*gc_parsing;
	t_lst_cmd	*cmd;
	t_lst_env	*env;
}	t_global;

typedef struct s_dual_int
{
	int	a;
	int	b;
	int	c;
}	t_dual_int;

//  ------------------------------------------------
//  < ------------ GARBADGE COLLECTOR ------------ >
//  ------------------------------------------------

//create a new gc chain
t_gc		*ft_gc_new(void *var, const char *er, t_global *g);
//link a new gc chain to the list (S.O.L.)
void		*ft_gc_add_front(t_gc **alst, t_gc *new);
//link a new gc chain to the list or create the list if NULL (E.O.L.)
void		*ft_gc_add_back(t_gc **alst, t_gc *new);
//return the last chain of the list
t_gc		*ft_gc_last(t_gc *lst);
//free the current chain and the pointer inside
void		ft_gc_delone(t_gc *lst);
//free the whole list and their pointers
void		ft_gc_clear(t_gc **lst);

int			ft_gc_size(t_gc *lst);

//  ------------------------------------------------
//  < ------------        UTILS       ------------ >
//  ------------------------------------------------

//take a part of a string
char		*ft_substr(char const *s, unsigned int start, size_t len, \
			t_global *g);
//give the lenght of the string
size_t		ft_strlen(const char *str);
size_t		ft_strstrlen(char **str);
//allocate the string passed in parameter
char		*ft_strdup(const char *s1, t_global *g);

int			ft_isalnum(int c);

char		*ft_strjoin(char *s1, char *s2, t_global *g);

int			ft_nstrncmp(const char *s1, const char *s2, size_t n, size_t start);

char		*ft_itoa(int n, t_global *g);

int			ft_atoi(const char *str);

void		ft_putendl_fd(char	*s, int fd);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		**ft_split(char const *s, char c, t_global *g);

void		ft_putstr_fd(char	*s, int fd);

int			ft_isdigit(int c);

char		*remove_quote(char *str, t_global *g);

t_lst_env	*cmp_env_key(int *i, char *str, t_lst_env *tmp);

void		close_fds(int *fd_in, int *fd_out);

//  ------------------------------------------------
//  < ------------      CHECKER       ------------ >
//  ------------------------------------------------

//check if the cmd is filled with nothing more than space, skip line, tab ...
int			check_isempty(char *cmd);
//check if the cmd have a correct format of pipe
int			check_pipe(char *cmd, int i, int state);
//check if the redirection are valid
int			check_redirection(char *cmd, int i, int state);

int			check_char_isempty(char c);

int			check_file_dir(char *str, t_global *g, int mode);

int			check_has_cmd(t_lst_cmd *cmd, t_global *g);

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
int			ft_lst_env_size(t_lst_env *lst);

t_lst_env	*ft_lst_env_new(char **key, char **value);
t_lst_env	*ft_lst_env_last(t_lst_env *lst);
void		ft_lst_env_add_back(t_lst_env **alst, t_lst_env *new, t_global *g);
void		ft_lst_env_del_in(t_lst_env *lst, t_global *g);

//  ------------------------------------------------
//  < ------------   PARSING COMMAND  ------------ >
//  ------------------------------------------------

void		ft_split_shell(t_lst_cmd **cmd, t_global *mini_sh);
int			define_cmd(t_global *mini_sh);
void		define_exec(t_lst_cmd **lst, t_global *g, int i);
int			check_redirect_has_fd(t_lst_cmd *cmd);

char		*rebuild_command(t_lst_cmd *cmd, t_global *g);
void		replace_env_v(t_lst_parse **lst, t_lst_cmd **cmd, t_global *g, \
			char *r);

void		skip_quote(char *str, int *i);
void		skip_word(char *str, int *i);
void		skip_to_next_word(char *str, int *i);
void		skip_redirection(char *str, int *i);

int			make_lst_cmd(char *cmd, t_global *mini_sh, int i, int j);
int			print_er(const char *er);
int			print_er(const char *er);
void		kill_my_child(t_global *g, int status, int l_status);

void		shlvl_plus_one(char **key, char **value, t_dual_int *forced_env);
void		add_env_(t_global *g);
void		add_oldpwd(t_lst_env **lst_env, t_global *g);
void		add_pwd(t_lst_env **lst_env, t_global *g);
void		add_shlvl(t_lst_env **lst_env, t_global *g);
void		parse_env(char *current, t_lst_env **lst_env, t_global *g, \
			t_dual_int *forced_env);
void		load_env(char **env, t_lst_env **lst_env, t_global *g);

//  ------------------------------------------------
//  < ------------      READLINE      ------------ >
//  ------------------------------------------------

void		main_mini_sh(t_global *mini_sh);

//  ------------------------------------------------
//  < ------------      BUILT-IN      ------------ >
//  ------------------------------------------------

//sort to see if it's a built in and execute it
void		sort_build_in(t_lst_cmd **cmd, t_global *mini_sh);

// < --- EXPORT --- >
void		b_in_export(t_lst_cmd **cmd, t_global *mini_sh);
// < --- EXPORT UTILS --- >
void		print_export(t_lst_env *env);
void		exec_export(t_global *mini_sh, char *str);
int			is_valid_key_char(char c, char mode);
int			skip_key(char *str, int *i, int first, int mode);
int			is_valid_key_char(char c, char mode);
char		*skip_value(char *str, int *i, t_global *g);
void		export_put_value(char *key, char *value, t_global *g, \
			t_lst_env **env);

// < --- EXIT --- >
void		b_in_exit(t_global *mini_sh);

// < --- PWD --- >
void		b_in_pwd(t_global *mini_sh);

// < --- CD --- >
void		b_in_cd(t_global *mini_sh, t_lst_cmd **cmd);

// < --- ECHO --- >
void		b_in_echo(t_global *mini_sh, t_lst_cmd **cmd);

// < --- ENV --- >
void		b_in_env(t_global *mini_sh, t_lst_cmd **cmd);

// < --- UNSET --- >
void		b_in_unset(t_lst_cmd **cmd, t_global *g);

//  ------------------------------------------------
//  < ------------      EXEC          ------------ >
//  ------------------------------------------------

void		exec_cmd(t_global *mini_sh, pid_t pid, int status);
void		exec_built_in(t_global *mini_sh, t_lst_cmd **cmd);
char		**rebuild_env(t_lst_env *env, t_global *g);
void		check_fd_in(int *fd_in, int *fd_out, t_lst_cmd *cmd, \
			t_global *g);
void		check_fd_out(int *fd_in, int *fd_out, t_lst_parse *tmp, \
			t_global *g);
void		right_redirect(int *fd_in, int *fd_out, t_lst_parse *tmp, \
			t_global *g);
void		right_right_redirect(int *in, int *out, t_lst_parse *tmp, \
			t_global *g);

//ERROR MANAGER 
//return 0
int			print_er(const char *er);
//ERRR MANAGER
int			check_path(t_global *mini_sh, t_lst_cmd *cmd);
int			is_relative(t_global *mini_sh, t_lst_cmd *cmd);
void		cmd_not_vld(t_global *mini_sh, t_lst_cmd *cmd);
//exit program because of a malloc error.
void		malloc_exit(t_global *g, const char *er);

//yes i know
int			check_no_arg(t_lst_cmd **cmd, char *er_cmd, t_global *g);
char		*get_binary(t_global *mini_sh, t_lst_cmd *cmd);
char		*get_path(t_global *mini_sh);
int			complicado(t_global *mini_sh, t_lst_cmd *cmd, int fd_in, \
			pid_t *c_pid);

// SIGNALS
int			sig_child_hndlr(const int signal);
int			sig_child_hndlr_in_cmd(const int signal);
void		static_signal(void	*ptr, int sig);
void		sig_ctrl_d(t_global *mini_sh);
void		static_signal(void	*ptr, int sig);

#endif
