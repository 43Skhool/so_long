
// MAP MUST BE:
//  rectangular
//  surrended by walls

// MAP MUST CONTAINS:
//  1 exit
//  >= 1 collectibles
//  1 starting position

// There must be a valid path

#include "so_long.h"

static bool is_surrended_by_walls(char *map[]);

static bool validate_components(char *map[], map_validation_response *response); // se ritorna x:-1 e y:-1 vuol dire che ci sono troppe starting position, altrimenti la posizione iniziale del giocatore

static bool valid_path_exist(char *map[], position *player_position);

//Validate the content of the maps
map_validation_response *validate_map(char *map[])
{
	map_validation_response *result;
	position *player_starting_position;

	result = malloc(sizeof(map_validation_response));
	if (!result)
		return (result->valid = false, result->reason = "Memory allocation failed", result);
	//WE ALREADY KNOW THAT IS A RECTANGULAR
	if (is_surrended_by_walls(map) == false)
		return (result->reason = "Map isn't surrended by walls", result);
	if (validate_components(map, result) == false)
		return (result);
	if (valid_path_exist(map, result->player_starting_position) == false)
		return (result->reason = "Map isn't surrended by walls", result);

	result->valid = true;
	return (result);
}


static bool is_surrended_by_walls(char *map[])
{
	//'i' is used to pass through the rows of matrix
	int	i;
	//'j' is used to pass through the the line
	int	j;

	size_t	column_number;

	i = 1;//Start from the second one beacause the first is checked in the last step
	j = 0;
	column_number = ft_strlen(map[0]);

	while (map[i + 1])
	{
		if (map[i][0] != WALL || map[i][column_number - 1] != WALL)
			return (false);
		i++;
	}

	//Now 'i' has become the number of the last row
	while (j < column_number)
	{
		if (map[0][j] != WALL || map[i][j] != WALL)
			return (false);
		j++;
	}

	return (true);
}

static bool validate_components(char *map[], map_validation_response *response)
{
	//'i' is used to pass through the rows of matrix
	int	i;
	//'j' is used to pass through the the line
	int	j;
	int	exit_count;
	int	player_position_count;
	int	collectibles_count;

	//Border are already checked in 'is_surrended_by_walls'
	i = 1;
	j = 1;

	player_position_count = 0;
	collectibles_count = 0;
	exit_count = 0;

	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == PLAYER)
				player_position_count++;
			else if (map[i][j] == COLLECTIBLES)
				collectibles_count++;
			else if (map[i][j] == EXIT)
				exit_count++;
			else if (map[i][j] != WALL && map[i][j] != FLOOR)//Altro
				return (response->reason = "Found unknown element", false);
			j++;
		}
		i++;
	}
	if (player_position_count != 1)
		return (response->reason = "Wrong number of player position, it should be 1", false);
	else if (collectibles_count < 1)
		return (response->reason = "Wrong number of collectibles, it should be 1 on more", false);
	else if (exit_count != 1)
		return (response->reason = "Wrong number of exit, it should be 1", false);

	return (response->valid = true, true);
}

static bool valid_path_exist(char *map[], position *player_position)
{
	// TO DO
	return (false);
}
