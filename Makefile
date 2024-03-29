# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:17:44 by alvachon          #+#    #+#              #
#    Updated: 2023/01/24 19:53:57 by alvachon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := pipex
CC       := gcc
FLAGS    := -Wall -Wextra -Werror

SRCS        :=      src/pipex.c \
					src/execute.c \
					src/path.c \
					src/return.c

                          
OBJS        := $(SRCS:.c=.o)

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"


fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


