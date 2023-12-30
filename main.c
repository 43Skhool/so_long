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

	game *result = get_map(argv[1]);

	if (!result)
		printf("error, memory allocation fail");
	else if (result->is_map_valid == false)
		printf("%s\n", result->reason);
	else
	{
		printf("ok, map is valid\n");
		print_char_matrix(result->map);
	}

	printf("player at %d, %d\n", result->player_starting_position->x,result->player_starting_position->y);
	printf("\n|%c|\n", result->map[result->player_starting_position->x][result->player_starting_position->y]);
	//window_init(result);
	dealloc_matrix(result->map);
	free_game(result);
}
