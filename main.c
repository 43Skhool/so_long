#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

void try_move(game *game)
{
	for (size_t i = 0; i < 4; i++)
	{
		printf("\n");
		print_char_matrix(game->map);
		if (move(game, RIGHT_ARROW) == true)
		{
			printf("\n|END|\n");
			return;
		}
	}

	printf("\narrivato a destra\n");
	print_char_matrix(game->map);

	if (move(game, LEFT_ARROW) == true)
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

	game *game = get_map(argv[1]);

	if (!game)
		printf("error, memory allocation fail");
	else if (game->is_map_valid == false)
		printf("%s\n", game->reason);
	else
	{
		//try_move(game);
	}

	// printf("player at %d, %d\n", game->player_position->x,game->player_position->y);
	// printf("\n|%c|\n", game->map[game->player_position->x][game->player_position->y]);
	window_init(game);

	// position p = *game->player_starting_position;
	// printf("%i", p.x);

	dealloc_matrix(game->map);
	free_game(game);
}
