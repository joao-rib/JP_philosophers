NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
#LFT_FLAGS = -lft
RM = rm -fr
MAIN = philo.c
SRC = Utils/*.c Utils_mtx/*.c Meal/*.c
#SRC_LFT = libft
OBJ = obj/*.o

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
#	@$(CC) $(FLAGS) $(OBJ) -L $(SRC_LFT) $(LFT_FLAGS) -o $(NAME)

$(OBJ): $(MAIN) $(SRC)
#	@make -C $(SRC_LFT) -s
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(SRC) $(MAIN)
	@mv *.o obj/

clean:
	@$(RM) $(OBJ) obj
#	@make clean -C $(SRC_LFT) -s

fclean:
	@$(RM) $(OBJ) $(NAME) obj
#	@make fclean -C $(SRC_LFT) -s

re: fclean all
