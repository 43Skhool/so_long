#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

#include <stdio.h>//TODO da levare

# define WALL			'1'
# define FLOOR			'0'
# define COLLECTIBLES	'C'
# define PLAYER			'P'
# define EXIT			'E'

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map_validation_response
{
	bool		valid;
	char		*reason;//Null if valid == true
	position	*player_starting_position;//Null if valid == false
	position	*exit_position;
	int			collectibles_count;
	char		**map;
}	map_validation_response;

map_validation_response	*get_map(char *file_name);

void	dealloc_matrix(char **matrix);

char **duplicate_char_matrix(char	**matrix);

size_t	count_matrix_row(char    **matrix);

void free_map_validation_response(map_validation_response *map_validation_response);

char	*get_next_line(int fd, bool last_call);

void print_char_matrix(char **matrix);

#endif
