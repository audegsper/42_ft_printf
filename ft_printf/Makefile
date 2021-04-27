NAME		= libftprintf.a
SRCS		= ./ft_printf.c 	\
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
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	$(LIB) $(NAME) $(OBJS)
clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
re : fclean all
.PHONY: all clean fclean re
