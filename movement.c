/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:22:43 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/03 00:50:21 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game_status	switch_position(t_game *game, t_position newposition)
{
	t_game_status	status;

	status = moved;
	if (game->map[newposition.x][newposition.y] == EXIT)
		if (game->collectibles_count == 0)
			status = win;
	if (game->map[newposition.x][newposition.y] == ENEMY)
		status = lose;
	game->map[newposition.x][newposition.y] = PLAYER;
	if (game->exit_position->x == game->player_position->x)
	{
		if (game->exit_position->y == game->player_position->y)
			game->map[game->player_position->x][game->player_position->y] = 'E';
		else
			game->map[game->player_position->x][game->player_position->y] = '0';
	}
	else
		game->map[game->player_position->x][game->player_position->y] = FLOOR;
	game->player_position->x = newposition.x;
	game->player_position->y = newposition.y;
	return (status);
}

static t_game_status	try_move(t_game *game, t_position newposition)
{
	if (game->map[newposition.x][newposition.y] == WALL)
		return (playing);
	else if (game->map[newposition.x][newposition.y] == COLLECTIBLES)
		game->collectibles_count--;
	return (switch_position(game, newposition));
}

t_game_status	move(t_game *game, int direction)
{
	t_position	new_position;

	new_position = *game->player_position;
	if (direction == W_KEY || direction == UP_ARROW)
	{
		game->player_direction = direction;
		return (new_position.x--, try_move(game, new_position));
	}
	else if (direction == S_KEY || direction == DOWN_ARROW)
	{
		game->player_direction = direction;
		return (new_position.x++, try_move(game, new_position));
	}
	else if (direction == D_KEY || direction == RIGHT_ARROW)
	{
		game->player_direction = direction;
		return (new_position.y++, try_move(game, new_position));
	}
	else if (direction == A_KEY || direction == LEFT_ARROW)
	{
		game->player_direction = direction;
		return (new_position.y--, try_move(game, new_position));
	}
	return (playing);
}
