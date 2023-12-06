
#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

size_t	count_matrix_row(char    **matrix);
char **duplicate_char_matrix(char	**matrix);
void	dealloc_matrix(char **matrix);

char ** inizializza_quella_mmerda()
{
    int N = 8;
    char **map;
    map = malloc(sizeof(char *) * N - 1);

    for (size_t i = 0; i < N; i++)
        map[i] = malloc(sizeof(char) * 6);

    ft_strlcpy(map[0], "11111", 6);
    ft_strlcpy(map[1], "1C0C1", 6);
    ft_strlcpy(map[2], "1P1C1", 6);
    ft_strlcpy(map[3], "101E1", 6);
    ft_strlcpy(map[4], "11111", 6);
    ft_strlcpy(map[5], "11111", 6);
    ft_strlcpy(map[6], "11111", 6);

    map[7] = NULL; // TO DO MAP MUST BE NULL TERMINATED

    return (map);
}

static void stampa_quella_mmerda(char **map)
{
    int i = 0;

    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }

}

static void libera_quella_mmerda(char **map)
{
    int i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int main(/*int argc, char *argv[]*/)
{
	char **map = inizializza_quella_mmerda();
    //stampa_quella_mmerda(map);

    //printf("\n");

    // char **dup = duplicate_char_matrix(map);

    // stampa_quella_mmerda(dup);

    // printf("|%li|\n", count_matrix_row(map));

	// char *file_path = "maps/valid_map1";

	// map_validation_response *a = get_map(file_path, map);

	// if (a->valid == false)
	// 	printf("%s\n", a->reason);
	// else
	// 	printf("ok, map is valid\n");

    // free(a->exit_position);
    // free(a->player_starting_position);
    // free(a->reason);
    // free(a);//Necessario per non avere memory leak con il valgrind nei test
    //dealloc_matrix(dup);
    libera_quella_mmerda(map);
}
