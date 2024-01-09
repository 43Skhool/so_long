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

void		validate_map(t_game *game);
static bool	is_surrended_by_walls(char *map[]);
bool		validate_components(t_game *game);
static void	try_reach(char **map, t_position start_pos, int *exit, int *n_coll);

void	validate_map(t_game *game)
{
	char	**tmp_matrix;
	int		exit;
	int		collectibles;

	exit = 0;
	collectibles = 0;
	if (is_surrended_by_walls(game->map) == false)
	{
		game->reason = "Map isn't surrended by walls";
		return ;
	}
	if (validate_components(game) == false)
		return ;
	tmp_matrix = duplicate_char_matrix(game->map);
	try_reach(tmp_matrix, *game->player_position, &exit, &collectibles);
	game->is_map_valid = false;
	if (collectibles != game->collectibles_count)
		game->reason = "Not all collectibles are reachable";
	else if (exit == 0)
		game->reason = "Exit isn't reachable";
	else
		game->is_map_valid = true;
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

// n_coll: number of collectibles, exit: if exit is reachble
static void	try_reach(char **map, t_position start_pos, int *exit, int *n_coll)
{
	int			x;
	int			y;

	x = start_pos.x;
	y = start_pos.y;
	if (map[x][y] == EXIT)
		*exit = 90;
	if (map[x][y] == COLLECTIBLES)
		(*n_coll)++;
	if (map[x][y] == WALL || map[x][y] == 'v' || map[x][y] == ENEMY)
		return ;
	map[x][y] = 'v';
	start_pos.x = x + 1;
	start_pos.y = y;
	try_reach(map, start_pos, exit, n_coll);
	start_pos.x = x;
	start_pos.y = y + 1;
	try_reach(map, start_pos, exit, n_coll);
	start_pos.x = x - 1;
	start_pos.y = y;
	try_reach(map, start_pos, exit, n_coll);
	start_pos.x = x;
	start_pos.y = y -1;
	try_reach(map, start_pos, exit, n_coll);
	return ;
}
