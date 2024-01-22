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
# define ENEMY			'M'//mina
# define TILE_SIZE		64
# define DESTROY_NOTIFY 17
# define KEY_ESC		65307
# define W_KEY			119
# define R_KEY			114
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

typedef enum e_game_status
{
	win,
	lose,
	playing,
	moved,
} game_status;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_game
{
	bool		is_map_valid;
	char		*reason;//Non va mai deallocata
	t_position	*player_position;
	t_position	*exit_position;
	int			collectibles_count;
	int			move_count;
	char		**map;
	int			number_of_columns;
	int			number_of_rows;
	char		*file;
	int			number_of_moves;
}	t_game;

typedef struct s_assets
{
	void	*wall;
	void	*floor;
	void	*player[2];
	void	*collectible;
	void	*exit;
	void	*enemy;
	void	*death[2];
	void	*win_1;
	void	*win_2;
}	t_assets;

typedef struct	s_vars {
	void					*mlx;
	void					*win;
	t_assets				*assets;
	t_game					*game;
	//t_data					*img;

}	t_vars;

t_game		*get_map(char *file_name);

void		dealloc_matrix(char **matrix);

char		**duplicate_char_matrix(char	**matrix);

size_t		count_matrix_row(char **matrix);

void		print_char_matrix(char **matrix);//TO DO da levare

void		start_game(t_game *map);

int end(t_vars *vars, bool restart);

void		free_game(t_game *game);

int		render_next_frame(t_vars *vars);

game_status	move(t_game *game, int direction);

int end_game(t_vars *vars);

//int		keyboard_handler(int direction, t_vars *vars);


#endif
