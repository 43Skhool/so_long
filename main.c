
#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

size_t	count_matrix_row(char    **matrix);
char **duplicate_char_matrix(char	**matrix);
void	dealloc_matrix(char **matrix);

char ** inizializza_quella_mmerda()
{
    size_t N = 5;
    char **map;
    map = malloc(sizeof(char *) * N);

    for (size_t i = 0; i < N - 1; i++)
        map[i] = malloc(sizeof(char) * 6);

    ft_strlcpy(map[0], "11111", 6);
    ft_strlcpy(map[1], "1C0C1", 6);
    ft_strlcpy(map[2], "1P101", 6);
    ft_strlcpy(map[3], "11111", 6);

    map[N - 1] = malloc(sizeof(char) * 1);
    map[N - 1] = '\0'; // TO DO MAP MUST BE NULL TERMINATED

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

int main(/*int argc, char *argv[]*/)
{
	char **map = inizializza_quella_mmerda();
    printf("mappa iniziale\n");
    stampa_quella_mmerda(map);
    printf("\n\n");
    //printf("\n");

    // char **dup = duplicate_char_matrix(map);

    // stampa_quella_mmerda(dup);

    // printf("|%li|\n", count_matrix_row(map));

	char *file_path = "maps/not_surrended_by_walls";

	map_validation_response *a = get_map(file_path, map);

	if (a->valid == false)
		printf("%s\n", a->reason);
	else
		printf("ok, map is valid\n");

    if (a->exit_position)
        free(a->exit_position);

    if (a->player_starting_position)
        free(a->player_starting_position);

    free(a);

    printf("\n\nmappa finale\n");
    stampa_quella_mmerda(map);
    printf("\n\n");

    dealloc_matrix(map);
}
