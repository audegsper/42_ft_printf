# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 21:24:23 by dohykim           #+#    #+#              #
#    Updated: 2021/05/03 23:00:23 by dohykim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
SRCS		= ./ft_printf.c \
			  ./parse.c \
			  ./print.c \
			  ./utils.c \

OBJS		= $(SRCS:.c=.o)
RM			= rm -f
LIB			= ar rc
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(LIB) $(NAME) $(OBJS)
clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
re : fclean all
.PHONY: all clean fclean re
