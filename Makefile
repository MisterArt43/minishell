# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abucia <abucia@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 15:22:30 by abucia            #+#    #+#              #
#    Updated: 2022/09/07 15:22:30 by abucia           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = src/parsing/main.c \
src/parsing/lst_handler.c \
src/parsing/garbadge_mem.c \
src/parsing/utils.c \
src/parsing/checker_cmd.c \
src/parsing/ft_split.c \
src/parsing/define_parsing.c \
src/exec/fork.c \
src/built_in/exit.c \
src/built_in/pwd.c \
src/built_in/cd.c \
src/built_in/echo.c \
src/built_in/env.c \
src/built_in/sort_built_in.c \




CC = gcc
OBJ = $(SRC:.c=.o)
HEADER = includes/header.h
READLINE_LIB = ./includes/readline-8.1
FLAG = -I./includes/readline-8.1/ -g3 # -fsanitize=address #-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) -o $(NAME) $(OBJ) $(FLAG) -L./includes/readline-8.1/shlib -lreadline

%.o : %.c $(HEADER)
	$(CC) $(FLAG) -c $< -o $@

re : fclean $(NAME)

clean :
	@rm -rf $(OBJ) $(OBJ_B)
	@echo "$(GREEN)************ $@ clean !$(RST)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(GREEN)************ $@ fclean !$(RST)"
