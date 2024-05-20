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
	enemy_movement.c \
	cleaning.c

FLAGS		= -Wall -Werror -Wextra -g

OBJS		= $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@${MAKE} -sC corekit
	@${MAKE} -sC mlx 2>/dev/null 1>/dev/null
	@cc $(OBJS) -lm -L$(COREKIT_PATH) -lcorekit -Lmlx -lmlx -lXext -lX11 -o $(NAME) -s

all:$(NAME)

%.o: %.c
	@cc -c $< -o $@ -I$(COREKIT_PATH)/includes -Imlx

clean:
	@rm -fr *.o
	@rm -fr **/*.o
	@${MAKE} -C corekit clean -s
	@${MAKE} -sC mlx clean;

fclean: clean
	@rm -f *.a
	@rm -f *.out
	@rm -f *.gch
	@rm -f $(NAME)
	@${MAKE} -C corekit fclean -s

re: fclean all

download:
		wget -q https://cdn.intra.42.fr/document/document/21656/minilibx-linux.tgz; \
		tar -xf minilibx-linux.tgz; \
		mv minilibx-linux mlx; \
		rm -f minilibx-linux.tgz; \

test: all
	 ./$(NAME) maps/map.ber

valgrind: all
	 valgrind --leak-check=full --track-origins=yes -s --show-leak-kinds=all ./$(NAME) maps/map.ber
