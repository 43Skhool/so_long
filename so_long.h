/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:14 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "corekit.h"

# define WALL			'1'
# define FLOOR			'0'
# define COLLECTIBLES	'C'
# define PLAYER			'P'
# define EXIT			'E'
# define ENEMY			'M'
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

// typedef enum e_bool
// {
// 	false,
// 	true
// }	t_bool;

typedef enum e_game_status
{
	win,
	lose,
	playing,
	moved,
}	t_game_status;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_game
{
	t_bool		is_map_valid;
	char		*reason;
	t_position	*player_position;
	t_position	*exit_position;
	int			collectibles_count;
	char		**map;
	int			number_of_columns;
	int			number_of_rows;
	char		*file;
	int			number_of_moves;
	int			player_direction;
}	t_game;

typedef struct s_assets
{
	void	*wall;
	void	*floor;
	void	*player_left[2];
	void	*player_right[2];
	void	*player_up[2];
	void	*player_down[2];
	void	*collectible;
	void	*exit_closed;
	void	*exit_open;
	void	*enemy;
	void	*death[2];
	void	*win;
}	t_assets;

typedef struct s_vars
{
	void					*mlx;
	void					*win;
	t_assets				*assets;
	t_game					*game;
}	t_vars;

t_game			*get_map(char *file_name);

void			dealloc_matrix(char **matrix);

char			**duplicate_char_matrix(char	**matrix);

size_t			count_matrix_row(char **matrix);

void			print_char_matrix(char **matrix);

void			start_game(t_game *game);

int				end(t_vars *vars, t_bool restart);

void			free_game(t_game *game);

int				render_next_frame(t_vars *vars);

t_game_status	move(t_game *game, int direction);

int				end_game(t_vars *vars);

int				put_img(t_vars *vars, void *asset, int x, int y);

#endif
