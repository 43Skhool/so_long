NAME		= so_long

SRC = map_validation/map_validation.c \
	map_validation/map_parsing.c \
	map_validation/map_content.c \
	utils.c \
	window_management/input_handling.c \
	window_management/window_handling.c \
	window_management/tile_render.c \
	movement.c \
	end_game.c \
	main.c

FLAGS		= -Wall -Werror -Wextra -g -s

$(NAME):
	${MAKE} -C libft bonus
	${MAKE} -C mlx
	cc $(SRC) -lm -Ilibft *.h -Llibft -lft -Imlx -Lmlx -lmlx -lXext -lX11
#TO DO rimettere le flag
#TO DO risolvere il relink

all: $(NAME)

clean:
	rm -f *.o
	cd ./libft/ && ${MAKE} clean

fclean: clean
	rm -f *.a
	rm -f *.out
	rm -f *.gch
	cd ./libft/ && ${MAKE} fclean

re: fclean all

test: re
	 ./a.out maps/movement_try.ber

val: re
	 valgrind --leak-check=full --show-leak-kinds=all ./a.out maps/movement_try.ber
