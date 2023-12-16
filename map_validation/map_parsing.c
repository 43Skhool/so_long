
#include "../so_long.h"

typedef struct	s_map_size {
	int	lines_number;
	int	columns_number; //-1 => non è un quadrato
}	map_size;

map_validation_response *validate_map(map_validation_response *result);
static bool validate_file_name(char *file_name);
static char **read_map(char *file_name, map_size *size);
static bool get_map_size(char *file_name, map_size *size);

map_validation_response *get_map(char *file_name)
{
	map_validation_response *result;
	result = malloc(sizeof(map_validation_response));
	if (!result)
		return (NULL);
	result->valid = false;
	result->exit_position = NULL;
	result->player_starting_position = NULL;
	result->map = NULL;

	if (validate_file_name(file_name) == false)
		return (result->reason = "Error, wrong file extension", result);

	map_size *size = malloc(sizeof(map_size));
	if (get_map_size(file_name, size) == false)
		return (result->reason = "Error, map isn't a rectangle", free(size), result);

	result->map = read_map(file_name, size);

	free(size);

	if (!result->map)
		return (result->reason = "Error during file lecture", result);

	result = validate_map(result);
	if (!result)
		return (result->reason = "Error during map validation", result);

	//result->valid= true;
	return (result);
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
static char **read_map(char *file_name, map_size *size)
{
	int	i;
	int	j;
	int	fd;
	char buffer[1];
	char **map;

	//buffer = ft_calloc(size->columns_number + 1, sizeof(char));
	i = 0;
	j = 0;
	map = ft_calloc(size->lines_number + 1, sizeof(char *));
	while(i < size->lines_number)
	{
		map[i] = ft_calloc(size->columns_number + 1, sizeof(char));
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
static bool get_map_size(char *file_name, map_size *size)
{
	int			fd;
	char		buffer[1];
	int			line_length;
	int			column_number;

	column_number = 0;
	line_length = 0;
	fd = open(file_name, O_RDONLY);
	size->lines_number = 0;
	size->columns_number = -1;
	while (read(fd, buffer, sizeof(buffer)))
	{
		if (*buffer == '\n')
		{
			size->lines_number++;
			if (size->columns_number != column_number && size->columns_number != -1)
				return (false);
			else
				size->columns_number = column_number;
			column_number = 0;
		}
		else if (*buffer != '\r')//carriage return
			column_number++;
	}
	close(fd);
	return (true);
}
