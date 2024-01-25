/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:17:31 by marvin            #+#    #+#             */
/*   Updated: 2024/01/24 18:17:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game_status	try_move(t_game *game, t_position newposition);
static t_game_status	switch_position(t_game *game, t_position newposition);

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
