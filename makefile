NAME		= so_long

SRC = map_validation/map_validation.c \
	map_validation/map_parsing.c \
	utils.c \
	main.c

FLAGS		= -Wall -Werror -Wextra

$(NAME):
	${MAKE} -C libft bonus
	${MAKE} -C mlx
	cc $(SRC) -lm -Ilibft *.h -Llibft -lft -Imlx -Lmlx -lmlx -lXext -lX11
#TO DO rimettere le flag

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
	 ./a.out

val: re
	 valgrind ./a.out
