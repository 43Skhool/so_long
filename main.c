#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

void try_move(t_game *game)
{
	game_status status;
	for (size_t i = 0; i < 4; i++)
	{
		printf("\n");
		print_char_matrix(game->map);
		status = move(game, RIGHT_ARROW);
		if (status == playing)
		{
			printf("\n|PLAYING|\n");
		}
		if (status == lose)
		{
			printf("\n|LOSE|\n");
			return;
		}
	}

	printf("\narrivato a destra\n");
	print_char_matrix(game->map);
	status = move(game, RIGHT_ARROW);
	if (status == win)
	{
		printf("\nEND\n");
	}

	print_char_matrix(game->map);
}

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
		// try_move(game);
		printf("rows: %i\n", game->number_of_rows);
		printf("cls: %i\n", game->number_of_columns);
		print_char_matrix(game->map);
		start_game(game);
		// free_game(game);
	}

	free_game(game);
}
