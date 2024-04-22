/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:14 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_bool	search_components(t_game *game, int	*n_exit, int *n_player);
static int		switch_element_type(t_game *game, int i, int j, int *n_exit);

t_bool	validate_content(t_game *game)
{
	int	exit_count;
	int	player_position_count;

	player_position_count = 0;
	game->collectibles_count = 0;
	exit_count = 0;
	game->player_position = malloc(sizeof(t_position));
	game->exit_position = malloc(sizeof(t_position));
	if (!game->exit_position || !game->player_position)
		return (false);
	if (search_components(game, &exit_count, &player_position_count) == false)
		return (game->reason = "found an unknow element", false);
	if (player_position_count != 1)
	{
		game->reason = "Wrong number of player position, it must be 1";
		return (false);
	}
	else if (game->collectibles_count < 1)
	{
		game->reason = "Wrong number of collectibles, it must be >= 1";
		return (false);
	}
	else if (exit_count != 1)
		return (game->reason = "Wrong number of exit, it should be 1", false);
	return (game->is_map_valid = true, true);
}

//false: found unkown element
static t_bool	search_components(t_game *game, int	*n_exit, int *n_player)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	tmp = 0;
	while (game->map[i])
	{
		j = 1;
		while (game->map[i][j])
		{
			tmp = switch_element_type(game, i, j, n_exit);
			if (tmp == -1)
				return (false);
			else if (tmp == 1)
				(*n_player)++;
			j++;
		}
		i++;
	}
	return (true);
}

//return number of player, -1: unknown element
static int	switch_element_type(t_game *game, int i, int j, int *exit_num)
{
	int	player_num;

	player_num = 0;
	if (game->map[i][j] == PLAYER)
	{
		game->player_position->x = i;
		game->player_position->y = j;
		player_num++;
	}
	else if (game->map[i][j] == COLLECTIBLES)
		game->collectibles_count++;
	else if (game->map[i][j] == EXIT)
	{
		game->exit_position->x = i;
		game->exit_position->y = j;
		(*exit_num)++;
	}
	else if (game->map[i][j] != WALL)
		if (game->map[i][j] != FLOOR && game->map[i][j] != ENEMY)
			return (-1);
	return (player_num);
}
