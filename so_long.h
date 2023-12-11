#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#include <stdio.h>//TODO da levare

# define WALL			'1'
# define FLOOR			'0'
# define COLLECTIBLES	'C'
# define PLAYER			'P'
# define EXIT			'E'

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
	position	*exit_position;
	int			collectibles_count;
}	map_validation_response;

map_validation_response	*get_map(char *file_name, char **map_matrix);
void	dealloc_matrix(char **matrix);
char **duplicate_char_matrix(char	**matrix);
size_t	count_matrix_row(char    **matrix);
int	ft_strcmp(char *s1, char *s2);

// size_t	ft_strlen(const char	*str);// TO DO da levare e rimpiazzare con la funzione dentro libft
// size_t	ft_strlcpy(char *dest, const char *src, size_t size); // TO DO da levare e rimpiazzare con la funzione dentro libft
// void	*ft_calloc(size_t nitems, size_t size);// TO DO da levare e rimpiazzare con la funzione dentro libft
// char	**ft_split(char const *s, char c);// TO DO da levare e rimpiazzare con la funzione dentro libft

#endif
