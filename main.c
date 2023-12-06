
#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

char ** inizializza_quella_mmerda()
{
    char **map;
    map = malloc(sizeof(char *) * 5);

    for (size_t i = 0; i < 5; i++)
        map[i] = malloc(sizeof(char) * 6);

    ft_strlcpy(map[0], "11111", 6);
    ft_strlcpy(map[1], "1C1C1", 6);
    ft_strlcpy(map[2], "1P1E1", 6);
    ft_strlcpy(map[3], "101C1", 6);
    ft_strlcpy(map[4], "11111", 6);
    map[5] = NULL; // TO DO MAP MUST BE NULL TERMINATED

    return (map);
}

int main(/*int argc, char *argv[]*/)
{
	char **map = inizializza_quella_mmerda();
	char *file_path = "maps/valid_map1";

	map_validation_response *a = get_map(file_path, map);

	if (a->valid == false)
		printf("%s\n", a->reason);
	else
		printf("ok, map is valid\n");

	// free(a);//Necessario per non avere memory leak con il valgrind nei test
}
