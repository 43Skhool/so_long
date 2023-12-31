#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

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
		printf("ok, map is valid\n");
		print_char_matrix(game->map);

		move(game, RIGHT_ARROW);
		printf("\n");
		print_char_matrix(game->map);
		printf("\n");

		move(game, UP_ARROW);
		printf("\n");
		print_char_matrix(game->map);
		printf("\n");

		move(game, UP_ARROW);
		printf("\n");
		print_char_matrix(game->map);
		printf("\n");

		move(game, RIGHT_ARROW);
		printf("\n");
		print_char_matrix(game->map);
		printf("\n");

		printf("|collectibles: %i|", game->collectibles_count);

		move(game, RIGHT_ARROW);
		printf("\n");
		print_char_matrix(game->map);
		printf("\n");

		printf("| collectibles: %i|\n", game->collectibles_count);
	}

	// printf("player at %d, %d\n", game->player_position->x,game->player_position->y);
	// printf("\n|%c|\n", game->map[game->player_position->x][game->player_position->y]);
	//window_init(game);

	// position p = *game->player_starting_position;
	// printf("%i", p.x);

	dealloc_matrix(game->map);
	free_game(game);
}
