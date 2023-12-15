
// MAP MUST BE:
//  rectangular
//  surrended by walls

// MAP MUST CONTAINS:
//  1 exit
//  >= 1 collectibles
//  1 starting position

// There must be a valid path

#include "../so_long.h"

typedef struct s_reachable_elements//Used to validate the reachability of the exit and the collectibles
{
	int	is_exit_reachable;//0: no, 1 Si
	int	reachable_collectibles_count;
}	reachable_elements;

static bool is_surrended_by_walls(char *map[]);

static bool validate_components(char *map[], map_validation_response *response);

static void check_reachability(char *map[], position *player_position, reachable_elements *elements);

//Validate the content of the maps
map_validation_response *validate_map(char *map[])
{
	map_validation_response	*result;
	reachable_elements		*elements;
	char					**tmp_matrix;

	result = malloc(sizeof(map_validation_response));
	if (!result)
		return (result->valid = false, result->reason = "Memory allocation failed", result);
	if (is_surrended_by_walls(map) == false)
		return (result->reason = "Map isn't surrended by walls", result);
	if (validate_components(map, result) == false)
		return (result);
	elements = malloc(sizeof(reachable_elements));
	elements->is_exit_reachable = 0;
	elements->reachable_collectibles_count = 0;
	tmp_matrix = duplicate_char_matrix(map);
	check_reachability(tmp_matrix, result->player_starting_position, elements);
	result->valid = false;
	if (elements->reachable_collectibles_count != result->collectibles_count)
		result->reason = "Not all collectibles are reachable";
	if (elements->is_exit_reachable == 0)
		result->reason = "Exit isn't reachable";
	else
		result->valid = true;
	free(elements);
	if(tmp_matrix)
		dealloc_matrix(tmp_matrix);

	return (result);
}

static bool is_surrended_by_walls(char *map[])
{
	//'i' is used to pass through the rows of matrix
	int	i;
	//'j' is used to pass through the the line
	size_t	j;

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
	response->player_starting_position = malloc(sizeof(position));
	response->exit_position = malloc(sizeof(position));

	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == PLAYER)
			{
				response->player_starting_position->x = i;
				response->player_starting_position->y = j;

				player_position_count++;
			}
			else if (map[i][j] == COLLECTIBLES)
				collectibles_count++;
			else if (map[i][j] == EXIT)
			{
				response->exit_position->x = i;
				response->exit_position->y = j;

				exit_count++;
			}
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
	else
	{
		response->collectibles_count = collectibles_count;

		if (exit_count != 1)
			return (response->reason = "Wrong number of exit, it should be 1", false);
	}

	return (response->valid = true, true);
}

static void check_reachability(char *map[], position *start_position, reachable_elements *elements)
{
	int			x;
	int			y;

	x = start_position->x;
	y = start_position->y;

	if(map[x][y] == EXIT)
		elements->is_exit_reachable = 1;

	if(map[x][y] == COLLECTIBLES)
		elements->reachable_collectibles_count++;

	if (map[x][y] == '1' || map[x][y] == 'v')
		return;

	map[x][y] = 'v';

	//Down
	start_position->x = x + 1;
	start_position->y = y;
	check_reachability(map, start_position, elements);

	//Right
	start_position->x = x;
	start_position->y = y + 1;
	check_reachability(map, start_position, elements);

	//UP
	start_position->x = x - 1;
	start_position->y = y;
	check_reachability(map, start_position, elements);

	//Left
	start_position->x = x;
	start_position->y = y -1;
	check_reachability(map, start_position, elements);
	return;
}
