NAME=philo
CC=gcc
FLAGS=-Wall -Werror -Wextra -pthread
SRCS=philo.c philo_utils.c philo_actions.c philo_sec_utils.c

all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
