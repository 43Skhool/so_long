NAME		= so_long

SRC = map_validation/map_validation.c \
	map_validation/map_parsing.c \
	get_next_line.c \
	utils.c \
	main.c

FLAGS		= -Wall -Werror -Wextra

$(NAME):
	${MAKE} -C libft bonus
	${MAKE} -C mlx
	cc $(SRC) -Ilibft -Iget_next_line *.h -Llibft -lft -Imlx -Lmlx -lmlx  -lXext -lX11 -o so_long.out
#TO DO da rimettere le flag

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
	 ./so_long.out

val: re
	 valgrind ./so_long.out
