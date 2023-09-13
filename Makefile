# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 10:35:31 by mdenguir          #+#    #+#              #
#    Updated: 2023/09/13 20:57:00 by mdenguir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = main.c utils.c parsing_utils.c lexing_utils.c expand.c exec_utils.c errors.c ./builtins/pwd.c ./builtins/echo.c ./builtins/cd.c ./builtins/env.c ./builtins/export.c\
./builtins/unset.c ft_split.c ./execution/exec_one.c  ./execution/duplication.c free_data.c print_cmd.c ft_itoa.c

OBJECTS = ${SOURCES:.c=.o}

NAME = minishell

all : ${NAME}

CC = cc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

%.o:%.c
	${CC} ${CFLAGS} -o $@ -c $^

${NAME} : ${OBJECTS}
	${CC}   ${CFLAGS} -lreadline ${OBJECTS} -o ${NAME} -L/goinfre/mdenguir/homebrew/opt/readline/lib
# -L/goinfre/mdenguir/homebrew/opt/readline/lib #-I/goinfre/obouhrir/homebrew/opt/readline/include/
clean :
	rm -f ${OBJECTS}

fclean :
	rm -f ${OBJECTS} ${NAME}

re : fclean all


	