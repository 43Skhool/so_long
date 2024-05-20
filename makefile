NAME		= so_long

LIBFT_PATH = ./libft

SRC = main.c \
	map_validation.c \
	map_parsing.c \
	map_content.c \
	utils.c \
	hooking.c \
	window_handling.c \
	rendering.c \
	finish_game.c \
	movement.c \
	enemy_movement.c \
	cleaning.c

FLAGS		= -Wall -Werror -Wextra -g

OBJS		= $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@${MAKE} -sC libft bonus
	@${MAKE} -sC mlx
	@cc $(OBJS) -lm -L$(LIBFT_PATH) -lft -Lmlx -lmlx -lXext -lX11 -o $(NAME) -s

all:$(NAME)

%.o: %.c
	@cc -c $< -o $@ -I$(LIBFT_PATH) -Imlx

clean:
	@rm -fr *.o
	@rm -fr **/*.o
	@${MAKE} -sC libft clean
	@${MAKE} -sC mlx clean

fclean: clean
	@rm -f *.a
	@rm -f *.out
	@rm -f *.gch
	@rm -f $(NAME)
	@${MAKE} -C libft fclean -s

re: fclean all

download:
		wget -q https://cdn.intra.42.fr/document/document/21656/minilibx-linux.tgz; \
		tar -xf minilibx-linux.tgz; \
		mv minilibx-linux mlx; \
		rm -f minilibx-linux.tgz; \

test: all
	 ./$(NAME) maps/map.ber

valgrind: all
	 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) maps/map.ber
