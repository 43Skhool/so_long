
#include "../so_long.h"

map_validation_response *validate_map(char **map, map_validation_response *result);
static bool validate_file_name(char *file_name);
static bool read_map(char *file_name, char **map);

map_validation_response *get_map(char *file_name, char **map)
{
	map_validation_response *result;
	result = malloc(sizeof(map_validation_response));
	if (!result)
		return (NULL);
	result->valid = false;
	result->exit_position = NULL;
	result->player_starting_position = NULL;

	if (validate_file_name(file_name) == false)
		return (result->reason = "Error, wrong file extension", result);

	// Try to store the file content in the matrix
	//  if (read_map(file_name, map) == false)//Lettura del file fallita
	//  {
	//  	result = malloc(sizeof(map_validation_response));
	//  	result->valid = false;
	//  	if (!result)
	//  		return (NULL);
	//  	result->reason = "Error during file lecture, wrong format";
	//  	return (result);
	//  }

	result = validate_map(map, result);
	// Validation the readen map and returning the result
	return (result);

	// return (NULL);
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
static bool read_map(char *file_name, char **map)
{
	char *line;
	int fd;
	// int		i;
	size_t line_lenght;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	printf("|%s|aaa\n", line);
	if (!line)
		return (false);
	line_lenght = ft_strlen(line);
	while (line)
	{
		*map = line;
		line = get_next_line(fd);
		if (line_lenght != ft_strlen(line))
			return (false);
		printf("c");
	}
	return (true);
}
