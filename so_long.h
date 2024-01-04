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
# define SPRITE_HEIGHT	32
# define DESTROY_NOTIFY 17
# define KEY_ESC		65307
# define W_KEY			119
# define A_KEY			97
# define S_KEY			115
# define D_KEY			100
# define UP_ARROW		65362
# define LEFT_ARROW		65361
# define DOWN_ARROW		65364
# define RIGHT_ARROW	65363

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

typedef struct s_game
{
	bool		is_map_valid;
	char		*reason;//Non va mai deallocata
	position	*player_position;
	position	*exit_position;
	int			collectibles_count;
	char		**map;
}	game;

typedef struct	s_vars {
	void					*mlx;
	void					*win;
	t_data					*img;
	game					*map;
}				t_vars;

game	*get_map(char *file_name);

void	dealloc_matrix(char **matrix);

char	**duplicate_char_matrix(char	**matrix);

size_t	count_matrix_row(char **matrix);

void	free_game(game *map_validation_response);

void	print_char_matrix(char **matrix);//TO DO da levare

void	window_init(game *map);

int		window_close(int keycode, t_vars *vars);

int		render_next_frame(t_vars vars);

void	hook(t_vars *vars);

bool	move(game *game, int direction);

int		keyboard_handler(int direction, t_vars *vars);


#endif
