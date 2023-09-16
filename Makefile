# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 10:35:31 by mdenguir          #+#    #+#              #
#    Updated: 2023/09/15 20:55:03 by mdenguir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = main.c \
./errors/syntax_errors.c ./errors/pipe_errors.c ./errors/redir_errors.c ./errors/quotes_errors.c\
./errors/redir_errors_utils.c\
./parsing/utils.c  ./parsing/parsing_utils.c ./parsing/lexing_utils.c  ./parsing/print_cmd.c\
./parsing/cmd_utils.c ./parsing/redir_utils.c ./parsing/quotes.c ./parsing/spaces.c\
./parsing/extract_args.c \
./builtins/pwd.c ./builtins/echo.c ./builtins/cd.c ./builtins/env.c ./builtins/export.c\
./builtins/unset.c ./builtins/env_export_utils.c \
./execution/exec_one.c ./execution/dup_redirections.c ./execution/duplication.c ./execution/exec_utils.c\
./expansion/expand.c ./expansion/expand_utils.c ./expansion/expand_states.c ./expansion/utils_1.c\
./clean_up/free_data.c  \
./utils/ft_itoa.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c\


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


	