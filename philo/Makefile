
NAME		= philo
SRCS		= main.c init.c parse.c
OBJS		= $(SRCS:.c=.o)
CC 		= cc
CFLAGS		= -Wall -Wextra -Werror -pthread

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:	$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re