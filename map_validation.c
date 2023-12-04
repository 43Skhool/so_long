
// MAP MUST BE:
//  rectangular
//  surrended by walls

// MAP MUST CONTAINS:
//  1 exit
//  >= 1 collectibles
//  1 starting position

// There must be a valid path

#include "so_long.h"

static bool is_rectangular(char *map[]);
static bool is_surrended_by_walls(char *map[]);

static bool validate_components(char *map[], map_validation_response *response); // se ritorna x:-1 e y:-1 vuol dire che ci sono troppe starting position, altrimenti la posizione iniziale del giocatore

static bool valid_path_exist(char *map[], position *player_position);

map_validation_response *validate_map(char *map[])
{
	map_validation_response	*result;
	position				*player_starting_position;

	result = malloc(sizeof(map_validation_response));
	if (!result)
		return (NULL);
 	result->valid = false;

	if (is_rectangular(map) == false)
		return (result->reason = "map isn't a rectangular", result);
	if (is_surrended_by_walls(map) == false)
		return (result->reason = "map isn't surrended by walls", result);
	if (validate_components(map, result) == false)
		return ( result);
	if (valid_path_exist(map, result->player_starting_position) == false)
		return (result->reason = "map isn't surrended by walls", result);

	result->valid = true;
	return (result);
}

static bool is_rectangular(char *map[])
{
	// TO DO
	return (true);
}

static bool is_surrended_by_walls(char *map[])
{
	// TO DO
	return (true);
}

static bool validate_components(char *map[], map_validation_response *response){

	response->reason = "cioa";
	response->valid = false;

	// TO DO

	return (response->valid);
}

static bool valid_path_exist(char *map[], position *player_position)
{
	// TO DO
	return (false);
}
