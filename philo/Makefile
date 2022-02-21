# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 09:41:32 by psaulnie          #+#    #+#              #
#    Updated: 2022/02/18 13:24:22 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/utils.c srcs/init.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CC = gcc
NAME = philo

.PHONY:	all clean fclean re

all: ${NAME}

${NAME}: ${OBJS} inc/philosophers.h Makefile
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all