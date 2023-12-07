
#include "so_long.h"

map_validation_response *validate_map(char **map);

bool	read_map(char *file_name, char **map);

map_validation_response *get_map(char *file_name, char **map)
{
	map_validation_response	*result;

	//Try to store the file content in the matrix
	// if (read_map(file_name, map) == false)//Lettura del file fallita
	// {
	// 	result = malloc(sizeof(map_validation_response));
	// 	if (!result)
	// 		return (NULL);

	// 	result->reason = "Error during file lecture";
	// 	result->valid = false;
	// 	return (result);
	// }

	result = validate_map(map);
	//Validation the readen map and returning the result
	return (result);

	//return (NULL);
}

<<<<<<< HEAD
//read the map from file and check if it's a rectangle
//abbastanza sicuro che in caso di una lettura non completa del file (del buffer statico),
//la parte rimanente della riga valga come memory leak alla fine del programma.

=======
//read the map from file and check if it's a rectangle and the file is .ber file
>>>>>>> 4d3d1cceec6380da69230642e6954d77e174c1ed
bool	read_map(char *file_name, char **map)
{
	char	*line;
	int		fd;
	int		i;
	int		line_lenght;

	fd = open(file_name);
	line = gnl(fd);
	if (!line)
		return (false);
	line_lenght = ft_strlen(line);
	while (line)
	{
		*map = line;
		line = gnl(fd);
		if (line_lenght != ft_strlen(line))
			return (false);
	}
	return (true);
}
