NAME		= so_long.a

$(NAME):
	${MAKE} -C libft bonus && mv libft/libft.a $(NAME)
	gcc *.c *.h -I./libft $(NAME)

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
