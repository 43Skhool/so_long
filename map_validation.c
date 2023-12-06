
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

static bool is_reachable(char *map[], position *player_position, position *exit_position);

static	void stampa_quella_mmerda(char **map)// TO DO da levare
{
    int i = 0;

    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }

}

//Validate the content of the maps
map_validation_response *validate_map(char *map[])
{
	map_validation_response *result;

	result = malloc(sizeof(map_validation_response));
	//result->reason = "ciai";
	if (!result)
		return (result->valid = false, result->reason = "Memory allocation failed", result);
	//WE ALREADY KNOW THAT IS A RECTANGULAR
	if (is_surrended_by_walls(map) == false)
		return (result->reason = "Map isn't surrended by walls", result);
	// //WE ALREADY KNOW THAT IS surrended by wall, so we don't need to take about about the borsers
	if (validate_components(map, result) == false)
		return (result);
	if (is_reachable(map, result->player_starting_position, result->exit_position) == false)
		return (result->reason = "Map hasn't a valid path", result->valid = false, result);

	stampa_quella_mmerda(map);

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
	else if (exit_count != 1)
		return (response->reason = "Wrong number of exit, it should be 1", false);

	return (response->valid = true, true);
}

//Used to validate the reachability both of colletibles and exit, node visited are 'V'
static bool is_reachable(char *map[], position *start_position, position *end_position)
{
	int			x;
	int			y;
	position	*new_possible_position;
	char		**backup_map;

	

	x = start_position->x;
	y = start_position->y;

	//printf("Current position: %i - %i : %c\n", x, y, map[x][y]);
	//printf("Current position: %i - %i : %c\n", end_position->x, end_position->y, map[end_position->x][end_position->y]);

	//verifica di essere arrivato alla destinazione
	if (x == end_position->x && y == end_position->y)
		return (true);

	if (map[x][y] == '1' || map[x][y] == 'v')
		return (false);

	map[x][y] = 'v';

	//Down
	start_position->x = x + 1;
	start_position->y = y;
	printf("Current position down: %i - %i : %c\n", start_position->x, start_position->y, map[start_position->x][start_position->y]);
	if (is_reachable(map, start_position, end_position) == true)
		return (true);

	//Right
	start_position->x = x;
	start_position->y = y + 1;
	printf("Current position right: %i - %i : %c\n", start_position->x, start_position->y, map[start_position->x][start_position->y]);
	if (is_reachable(map, start_position, end_position) == true)
		return (true);

	//UP
	start_position->x = x - 1;
	start_position->y = y;
	printf("Current position up: %i - %i : %c\n", start_position->x, start_position->y, map[start_position->x][start_position->y]);
	if (is_reachable(map, start_position, end_position) == true)
		return (true);

	//Left
	start_position->x = x;
	start_position->y = y -1;
		printf("Current position left: %i - %i : %c\n", start_position->x, start_position->y, map[start_position->x][start_position->y]);
	if (is_reachable(map, start_position, end_position) == true)
		return (true);

	//map[x][y] = 'v';

	//TO DO tutti i nodi visitati (V) devono ritornare vuoti (0)
	return (false);
}


// static bool is_reachable(char *map[], position *start_position, position *end_position)
// {
// 	int			x;
// 	int			y;
// 	position	*new_possible_position;

// 	x = player_position->x;
// 	y = player_position->y;
// 	new_possible_position = malloc(sizeof(position));

// 	if (x == exit_position->x && y == exit_position->y)
// 	{
// 		map[x][y] = '0';
// 		return (true);
// 	}

// 	if (map[x][y] == '0')
// 	{
// 		map[x][y] = '0';

// 		//Check rigth
// 		new_possible_position->x = player_position->x;
// 		new_possible_position->y = player_position->y + 1;
// 		if (valid_path_exist(map, new_possible_position, exit_position) == true)
// 			return (true);

// 		//Check down
// 		new_possible_position->x = player_position->x + 1;
// 		new_possible_position->y = player_position->y;
// 		if (valid_path_exist(map, new_possible_position, exit_position) == true)
// 			return (true);

// 		map[x][y] = '1';
// 	}

// 	return (false);
// }
