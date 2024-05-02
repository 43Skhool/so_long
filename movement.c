/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:14 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game_status	try_move(t_game *game, t_position newposition);
static t_game_status	switch_position(t_game *game, t_position newposition);
static void				move_enemy(t_vars *vars, int x, int y);
static void				try_move_enemy(t_vars *vars, t_position start, int end_x, int end_y);
int						enemy_movement(t_vars *vars);

t_game_status	move(t_game *game, int direction)
{
	t_position	newposition;

	newposition = *game->player_position;
	if (direction == W_KEY || direction == UP_ARROW)
	{
		game->player_direction = direction;
		return (newposition.x--, try_move(game, newposition));
	}
	if (direction == S_KEY || direction == DOWN_ARROW)
	{
		game->player_direction = direction;
		return (newposition.x++, try_move(game, newposition));
	}
	if (direction == D_KEY || direction == RIGHT_ARROW)
	{
		game->player_direction = direction;
		return (newposition.y++, try_move(game, newposition));
	}
	if (direction == A_KEY || direction == LEFT_ARROW)
	{
		game->player_direction = direction;
		return (newposition.y--, try_move(game, newposition));
	}
	return (playing);
}

static t_game_status	try_move(t_game *game, t_position newposition)
{
	if (game->map[newposition.x][newposition.y] == WALL)
		return (playing);
	if (game->map[newposition.x][newposition.y] == COLLECTIBLES)
		game->collectibles_count--;
	return (switch_position(game, newposition));
}

static t_game_status	switch_position(t_game *game, t_position newposition)
{
	t_game_status	status;

	status = moved;
	if (game->map[newposition.x][newposition.y] == 'E')
		if (game->collectibles_count == 0)
			status = win;
	if (game->map[newposition.x][newposition.y] == 'M')
		status = lose;
	game->map[newposition.x][newposition.y] = 'P';
	if (game->exit_position->x == game->player_position->x)
	{
		if (game->exit_position->y == game->player_position->y)
			game->map[game->player_position->x][game->player_position->y] = 'E';
		else
			game->map[game->player_position->x][game->player_position->y] = '0';
	}
	else
		game->map[game->player_position->x][game->player_position->y] = '0';
	game->player_position->x = newposition.x;
	game->player_position->y = newposition.y;
	return (status);
}

int	enemy_movement(t_vars *vars)
{
	static int	frame_count;
	int			i;
	int			j;

	if (frame_count == 1000)
	{
		i = 0;
		while (vars->game->map[i])
		{
			j = 0;
			while (vars->game->map[i][j])
			{
				if (vars->game->map[i][j] == ENEMY)
					move_enemy(vars, i, j);
				j++;
			}
			i++;
		}
	}
	if (frame_count == 2000)
		frame_count = 0;
	frame_count++;
	 return (1);
}

//0 => UP
//1 => RIGHT
//2 => DOWN
//3 => LEFT
static void move_enemy(t_vars *vars, int x, int y)
{
	int			rndm_nmb;
	t_position	start;


	start.x = x;
	start.y = y;

	rndm_nmb = rand() % 4;
	if (rndm_nmb == 0)
		try_move_enemy(vars, start, x, y-1);
	if (rndm_nmb == 1)
		try_move_enemy(vars, start, x+1, y);
	if (rndm_nmb == 2)
		try_move_enemy(vars, start, x, y+1);
	if (rndm_nmb == 3)
		try_move_enemy(vars, start, x-1, y);
}

static void	try_move_enemy(t_vars *vars, t_position start, int end_x, int end_y)
{
	if (vars->game->map[end_x][end_y] == PLAYER)
		finish_game(vars, lose);
	if (vars->game->map[end_x][end_y] == FLOOR)
	{
		vars->game->map[end_x][end_y] = ENEMY;
		vars->game->map[start.x][start.y] = FLOOR;
	}
}