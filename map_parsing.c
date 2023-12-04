
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
}

//read the map from file and check if it's a rectangle
bool	read_map(char *file_name, char **map)
{
	return (true);
}
