#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h


// char ** inizializza_quella_mmerda()
// {
// 	size_t N = 5;
// 	char **map;
// 	map = malloc(sizeof(char *) * N);

// 	for (size_t i = 0; i < N - 1; i++)
// 		map[i] = malloc(sizeof(char) * 6);

// 	ft_strlcpy(map[0], "11111", 6);
// 	ft_strlcpy(map[1], "1C0C1", 6);
// 	ft_strlcpy(map[2], "1P1E1", 6);
// 	ft_strlcpy(map[3], "11111", 6);

// 	map[N - 1] = '\0'; // TO DO MAP MUST BE NULL TERMINATED

// 	return (map);
// }

// static void stampa_quella_mmerda(char **map)
// {
// 	int i = 0;

// 	while (map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		i++;
// 	}

// }

int main(/*int argc, char *argv[]*/)
{
	// char **map;
	// char **map = inizializza_quella_mmerda();

	char *file_path = "maps/not_surrended_by_walls.ber";

	map_validation_response *result = get_map(file_path);

	if (!result)
		printf("error, memory allocation fail");
	else if (result->valid == false)
		printf("%s\n", result->reason);
	else
	{
		printf("ok, map is valid\n");
		print_char_matrix(result->map);
	}

	dealloc_matrix(result->map);
	free_map_validation_response(result);
	//window_test();
}
