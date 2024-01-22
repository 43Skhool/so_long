#include "so_long.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Specify a map file");
		return (0);
	}

	t_game *game = get_map(argv[1]);

	if (!game)
		printf("error, memory allocation fail");
	else if (game->is_map_valid == false)
		printf("%s\n", game->reason);
	else
	{
		// printf("\nrows: %i\n", game->number_of_rows);
		// printf("cls: %i\n\n", game->number_of_columns);
		// print_char_matrix(game->map);
		// printf("\n");
		start_game(game);
	}

	free_game(game);
}
