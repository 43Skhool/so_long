#include "so_long.h"

int main(int argc, char *argv[])
{
	t_game *game;
	if (argc != 2)
	{
		printf("Specify a map file\n");
		return (0);
	}

	game = get_map(argv[1]);

	if (!game)
		write(1, "Error, allocation failed\n", 25);
	if (game->is_map_valid == false)
	{
		write(1, game->reason, ft_strlen(game->reason));
		write(1, "\n", 1);
	}
	else if (1 == 1)
	{
		// printf("\nrows: %i\n", game->number_of_rows);
		// printf("cls: %i\n\n", game->number_of_columns);
		// print_char_matrix(game->map);
		// printf("\n");
		start_game(game);
	}

	free_game(game);
}
