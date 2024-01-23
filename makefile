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

FLAGS		= -Wall -Werror -Wextra -g -s

OBJS		= $(SRC:%.c=%.o)
$(NAME):
	${MAKE} -C libft bonus
	${MAKE} -C mlx
	cc -c $(SRC) -Ilibft -Imlx
	cc *.o -lm -Llibft -lft -Lmlx -lmlx -lXext -lX11  -o $(NAME)
#TO DO rimettere le flag
#TO DO non relinka nemmeno cambiando cose nei file
#TO DO mettere l'assegnazione del file name nel validate file name e levarlo sia dallo start che dal mai

all: $(NAME)

clean:
	rm -fr *.o
	rm -fr **/*.o
	cd ./libft/ && ${MAKE} clean
	# cd ./mlx/ && ${MAKE} clean

fclean: clean
	rm -f *.a
	rm -f *.out
	rm -f *.gch
	rm -f $(NAME)
	cd ./libft/ && ${MAKE} fclean

re: fclean all

test: re
	 ./$(NAME) maps/map.ber

val: re
	 valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/map.ber
