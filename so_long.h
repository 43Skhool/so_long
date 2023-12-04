#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdlib.h>

#include <stdio.h>//TODO da levare

# define WALL				'1'
# define FLOOR 				'0'
# define COINS  			'C'
# define PLAYER				'P'
# define MAP_EXIT 		 	'E'

typedef enum e_bool
{
	false,
	true
}	bool;

typedef struct s_position
{
	int	x;
	int	y;
}	position;

typedef struct s_map_validation_response
{
	bool		valid;
	char		*reason;//Null if valid == true
	position	*player_starting_position;//Null if valid == false
}	map_validation_response;

map_validation_response	*validate_map(char *map[]);

#endif
