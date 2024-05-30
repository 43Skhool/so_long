/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/05/21 17:48:26 by lebartol         ###   ########.fr       */
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
# include "libft.h"

//'Macro' are defined to rappresent the map component
//	=>easier to modify
# define WALL			'1'
# define FLOOR			'0'
# define COLLECTIBLES	'C'
# define PLAYER			'P'
# define EXIT			'E'
# define ENEMY			'M'

# define TILE_SIZE		64

//X11 Event
# define DESTROY_NOTIFY 17

//Keysym of keayboard
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
//The keycode is the numeric representation received by the kernel
//	when a key or a mouse button is pressed.
//The keysym is the value assigned to the keycode.
//Keysym is better beacause it doesn't depend by the kernel, it's an
//	abstraction of the key

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
	t_list		*enemies;
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

void			start_game(t_game *game);

int				end(t_vars *vars, t_bool restart);

void			free_game(t_game *game);

int				render_next_frame(t_vars *vars);

t_game_status	move(t_game *game, int direction);

int				end_game(t_vars *vars);

int				put_img(t_vars *vars, void *asset, int x, int y);

int				enemy_movement(t_vars *vars);

int				finish_game(t_vars *vars, t_game_status status);

t_bool			validate_content(t_game *game);

void			validate_map(t_game *game);

t_game			*allocate_game(t_game *game);

int				destroy_notify(t_vars *vars);

int				hook(t_vars *vars);

#endif
