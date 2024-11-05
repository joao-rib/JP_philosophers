NAME = philo

CC = cc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address
SRC = main.c \
		parsing.c \
		suport_funcs.c \
		exit_errors.c \
		innit_structs.c \
		meal.c \
		get_set.c \
		sync_utils.c \
		philo_acts.c \
		monitoring.c

SRC_PATH = ./src/
OBJ_PATH = ./obj/

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
