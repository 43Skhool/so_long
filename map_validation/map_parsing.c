
#include "../so_long.h"

t_game *validate_map(t_game *game);
static bool validate_file_name(char *file_name);
static char **read_map(char *file_name, t_game *game);
static bool get_map_size(char *file_name, t_game *game);

t_game *get_map(char *file_name)
{
	t_game *game;
	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->is_map_valid = false;
	game->exit_position = NULL;
	game->player_position = NULL;
	game->map = NULL;

	if (validate_file_name(file_name) == false)
		return (game->reason = "Error, wrong file extension", game);

	if (get_map_size(file_name, game) == false)
		return (game->reason = "Error, map isn't a rectangle or it is too small", game);

	game->map = read_map(file_name, game);

	if (!game->map)
		return (game->reason = "Error during file read", game);

	game = validate_map(game);
	if (!game)
		return (game->reason = "Error during map validation", game);

	return (game);
}

static bool validate_file_name(char *file_name)
{
	char **file_name_splitted;
	size_t row_count;
	int lenght;

	file_name_splitted = ft_split(file_name, '.');
	row_count = count_matrix_row(file_name_splitted);
	lenght = ft_strlen(file_name_splitted[row_count - 1]);
	if (ft_strncmp(file_name_splitted[row_count - 1], "ber", lenght) == 0)
	{
		dealloc_matrix(file_name_splitted);
		return (true);
	}
	dealloc_matrix(file_name_splitted);
	return (false);
}
// read the map from file and check if it's a rectangle
// abbastanza sicuro che in caso di una lettura non completa del file (del buffer statico),
// la parte rimanente della riga valga come memory leak alla fine del programma.

// read the map from file and check if it's a rectangle and the file is .ber file
static char **read_map(char *file_name, t_game *game)
{
	int	i;
	int	j;
	int	fd;
	char buffer[1];
	char **map;

	//buffer = ft_calloc(size->columns_number + 1, sizeof(char));
	i = 0;
	j = 0;
	map = ft_calloc(game->number_of_rows + 1, sizeof(char *));
	while(i < game->number_of_rows)
	{
		map[i] = ft_calloc(game->number_of_columns + 1, sizeof(char));
		i++;
	}

	i = 0;
	fd = open(file_name, O_RDONLY);
	while(read(fd, buffer, 1) > 0)
	{
		if (*buffer == '\n')
		{
			i++;
			j = 0;
		}
		else if (*buffer != '\r')//carriage return
		{
			map[i][j] = *buffer;
			j++;
		}
	}
	close(fd);
	return (map);
}

// read the file lookinf for the dimensions of the map to allow the allocation and returno false
// if the map isn't a rectangle
static bool get_map_size(char *file_name, t_game *game)
{
	int			fd;
	char		buffer[1];
	//int			line_length;
	int			column_number;

	column_number = 0;
	//line_length = 0;
	fd = open(file_name, O_RDONLY);
	game->number_of_rows = 1;
	game->number_of_columns = 0;
	while (read(fd, buffer, sizeof(buffer)) > 0)
	{
		if (*buffer == '\n')
		{
			game->number_of_rows++;
			if (game->number_of_columns != column_number && game->number_of_columns != 0)//1° line
				return (false);
			else
				game->number_of_columns = column_number;
			column_number = 0;
		}
		else if (*buffer != '\r')//carriage return
			column_number++;
	}
	close(fd);
	if (*buffer == '\n' || *buffer == '\r' || game->number_of_columns <= 1)
		return (false);
	return (true);
}
