/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:13:10 by maceccar          #+#    #+#             */
/*   Updated: 2024/01/09 16:13:10 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void		validate_map(t_game *result);
static bool	is_surrended_by_walls(char *map[]);
static bool	validate_components(char *map[], t_game *response);
static void	try_reach(char *map[], t_position player_position, t_reachable_elements *elements);

void	validate_map(t_game *result)
{
	t_reachable_elements	elements;
	char					**tmp_matrix;

	if (is_surrended_by_walls(result->map) == false)
	{
		result->reason = "Map isn't surrended by walls";
		return ;
	}
	if (validate_components(result->map, result) == false)
		return ;
	elements.is_exit_reachable = 0;
	elements.reachable_collectibles_count = 0;
	tmp_matrix = duplicate_char_matrix(result->map);
	try_reach(tmp_matrix, *result->player_position, &elements);
	result->is_map_valid = false;
	if (elements.reachable_collectibles_count != result->collectibles_count)
		result->reason = "Not all collectibles are reachable";
	if (elements.is_exit_reachable == 0)
		result->reason = "Exit isn't reachable";
	else
		result->is_map_valid = true;
	if (tmp_matrix)
		dealloc_matrix(tmp_matrix);
}

static bool	is_surrended_by_walls(char *map[])
{
	int		i;
	size_t	j;
	size_t	column_number;

	i = 1;
	j = 0;
	column_number = ft_strlen(map[0]);
	while (map[i + 1])
	{
		if (map[i][0] != WALL || map[i][column_number - 1] != WALL)
			return (false);
		i++;
	}
	while (j < column_number)
	{
		if (map[0][j] != WALL || map[i][j] != WALL)
			return (false);
		j++;
	}
	return (true);
}

static bool	validate_components(char *map[], t_game *game)
{
	int	i;
	int	j;
	int	exit_count;
	int	player_position_count;

	i = 1;
	j = 1;
	player_position_count = 0;
	game->collectibles_count = 0;
	exit_count = 0;
	game->player_position = malloc(sizeof(t_position));
	game->exit_position = malloc(sizeof(t_position));
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == PLAYER)
			{
				game->player_position->x = i;
				game->player_position->y = j;
				player_position_count++;
			}
			else if (map[i][j] == COLLECTIBLES)
				game->collectibles_count++;
			else if (map[i][j] == EXIT)
			{
				game->exit_position->x = i;
				game->exit_position->y = j;
				exit_count++;
			}
			else if (map[i][j] != WALL && map[i][j] != FLOOR && map[i][j] != ENEMY)
				return (game->reason = "Found unknown element", false);
			j++;
		}
		i++;
	}
	if (player_position_count != 1)
		return (game->reason = "Wrong number of player position, it should be 1", false);
	else if (game->collectibles_count < 1)
		return (game->reason = "Wrong number of collectibles, it should be 1 on more", false);
	else
	{
		game->collectibles_count = game->collectibles_count;
		if (exit_count != 1)
			return (game->reason = "Wrong number of exit, it should be 1", false);
	}
	return (game->is_map_valid = true, true);
}

static void	try_reach(char *map[], t_position start_position, t_reachable_elements *elements)
{
	int			x;
	int			y;

	x = start_position.x;
	y = start_position.y;
	if (map[x][y] == EXIT)
		elements->is_exit_reachable = 1;
	if (map[x][y] == COLLECTIBLES)
		elements->reachable_collectibles_count++;
	if (map[x][y] == WALL || map[x][y] == 'v' || map[x][y] == ENEMY)
		return ;
	map[x][y] = 'v';
	start_position.x = x + 1;
	start_position.y = y;
	try_reach(map, start_position, elements);
	start_position.x = x;
	start_position.y = y + 1;
	try_reach(map, start_position, elements);
	start_position.x = x - 1;
	start_position.y = y;
	try_reach(map, start_position, elements);
	start_position.x = x;
	start_position.y = y -1;
	try_reach(map, start_position, elements);
	return ;
}
