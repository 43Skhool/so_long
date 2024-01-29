NAME		= so_long

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

$(NAME): $(OBJS)
	${MAKE} -C libft bonus
	${MAKE} -C mlx
	cc $(FLAGS) -c $(SRC) -Ilibft -Imlx
	cc *.o -lm -Llibft -lft -Lmlx -lmlx -lXext -lX11  -o $(NAME)

all:$(NAME)

%.o: %.c
	cc -c $< -o $@ -Ilibft -Imlx

clean:
	rm -fr *.o
	rm -fr **/*.o
	${MAKE} -C libft clean
	${MAKE} -C mlx clean

fclean: clean
	rm -f *.a
	rm -f *.out
	rm -f *.gch
	rm -f $(NAME)
	${MAKE} -C libft fclean

re: fclean all

test: re
	 ./$(NAME) maps/map.ber

val: re
	 valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/big_map.ber
