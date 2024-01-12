NAME = philo

CINCLUDES = -I ./includes/



CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=thread

SRCS = ./sources/philo.c	./sources/parsing.c	./sources/utils.c\
		./sources/philo_rel.c	./sources/philo_cycle.c ./sources/actions.c\
		./sources/utils_2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@cc $(CFLAGS) $(CINCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re