/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:22:43 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/03 00:47:17 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	add_enemy_to_list(t_game *game, int x, int y)
{
	t_position	*new_enemy_position;

	new_enemy_position = malloc(sizeof(t_position));
	if (new_enemy_position)
	{
		new_enemy_position->x = x;
		new_enemy_position->y = y;
		ft_lstadd_front(&game->enemies, ft_lstnew(new_enemy_position));
	}
}

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
	else if (game->map[i][j] == ENEMY)
		add_enemy_to_list(game, i, j);
	else if (game->map[i][j] != WALL && game->map[i][j] != FLOOR)
		return (-1);
	return (player_num);
}

static t_bool	search_components(t_game *game, int *n_exit, int *n_player)
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

t_bool	validate_content(t_game *game)
{
	int	exit_count;
	int	player_position_count;

	player_position_count = 0;
	exit_count = 0;
	game->collectibles_count = 0;
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
