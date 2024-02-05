NAME		= so_long

COREKIT_PATH = ./corekit

SRC = main.c \
	map_validation/map_validation.c \
	map_validation/map_parsing.c \
	map_validation/map_content.c \
	utils.c \
	window_management/hooking.c \
	window_management/window_handling.c \
	window_management/rendering.c \
	window_management/finish_game.c \
	movement.c \
	cleaning.c

FLAGS		= -Wall -Werror -Wextra

OBJS		= $(SRC:%.c=%.o)

#-s used to silent terminal output
$(NAME): $(OBJS)
	@${MAKE} -sC corekit
	@${MAKE} -s -C mlx && echo "$(GREEN)[MLX]:\t\t MLX CREATED$(RESET)"
	@cc $(OBJS) -lm -L$(COREKIT_PATH) -lcorekit -Lmlx -lmlx -lXext -lX11 -o $(NAME) -s
	@echo "$(GREEN)[MLX]:\t\t PROJECT COMPILED$(RESET)"

all:$(NAME)

%.o: %.c
	@cc -c $< -o $@ -I$(COREKIT_PATH)/includes -Imlx -s

clean:
	rm -fr *.o
	rm -fr **/*.o
	@${MAKE} -C corekit clean -s && echo "$(RED)[COREKIT]:\t COREKIT CLEAN$(RESET)"
	@${MAKE} -C mlx clean -s && echo "$(RED)[MLX]:\t\t MLX CLEAN$(RESET)"

fclean: clean
	rm -f *.a
	rm -f *.out
	rm -f *.gch
	rm -f $(NAME)
	@${MAKE} -C corekit fclean -s && echo "$(RED)[COREKIT]:\t COREKIT FCLEAN$(RESET)"

re: download_corekit download_mlx fclean all

download_corekit:
	@wget https://github.com/Sheratan095/corekit.git
	rm -fr corekit.git

download_mlx:
	@wget https://cdn.intra.42.fr/document/document/21656/minilibx-linux.tgz
	@tar -xf minilibx-linux.tgz
	@mv minilibx-linux mlx
	@rm -f minilibx-linux.tgz

test: all
	 ./$(NAME) maps/map.ber

val: all
	 valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/map.ber

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m
