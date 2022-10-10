# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tschlege <tschlege@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 15:22:30 by abucia            #+#    #+#              #
#    Updated: 2022/10/02 20:20:56 by tschlege         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = src/parsing/main.c \
src/parsing/lst_handler.c \
src/parsing/garbadge_mem.c \
src/parsing/checker_cmd.c \
src/parsing/ft_split.c \
src/parsing/define_parsing.c \
src/parsing/utils.c \
src/parsing/utils2.c \
src/exec/fork.c \
src/built_in/export.c \
src/built_in/exit.c \
src/built_in/pwd.c \
src/built_in/cd.c \
src/built_in/echo.c \
src/built_in/env.c \
src/built_in/unset.c \
src/built_in/sort_built_in.c \
src/exec/exec_binary.c \
src/exec/ft_split.c \
src/exec/pipe_exec.c \
src/er_malloc.c \
src/exec/check_path.c \
src/exec/cmd_not_valid.c \
src/exec/rebuild_env.c \
src/built_in/export_utils.c \
src/built_in/built_in_utils.c \
src/exec/redirection.c \
src/parsing/parsing_utils.c \

CC = gcc
OBJ = $(SRC:.c=.o)
HEADER = includes/header.h
READLINE_LIB = ./includes/readline-8.1
FLAG = -I./includes/readline-8.1/ -g3 -Wall -Wextra -Werror #-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) -o $(NAME) $(OBJ) $(FLAG) -I ./includes/readline-8.1/libreadline.a -I ./includes/readline-8.1/libhistory.a -lreadline

%.o : %.c $(HEADER)
	$(CC) $(FLAG) -c $< -o $@

re : fclean $(NAME)

clean :
	@rm -rf $(OBJ) $(OBJ_B)
	@echo "$(GREEN)************ $@ clean !$(RST)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(GREEN)************ $@ fclean !$(RST)"
