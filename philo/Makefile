CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./parsing -I./exec -I./builtin -g3
LDFLAGS = -pthread

NAME = philo

SRCS = init.c  init2.c  main.c  routine.c  threads.c  utils.c  utils2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re