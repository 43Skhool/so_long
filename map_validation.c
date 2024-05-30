/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/05/20 17:57:07 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	try_reach(char **map, t_position s_pos, int *n_ex, int *n_col)
{
	int			x;
	int			y;

	x = s_pos.x;
	y = s_pos.y;
	if (map[x][y] == EXIT)
		*n_ex = 1;
	if (map[x][y] == COLLECTIBLES)
		(*n_col)++;
	if (map[x][y] == WALL || map[x][y] == 'v' || map[x][y] == ENEMY)
		return ;
	map[x][y] = 'v';
	s_pos.x = x + 1;
	s_pos.y = y;
	try_reach(map, s_pos, n_ex, n_col);
	s_pos.x = x;
	s_pos.y = y + 1;
	try_reach(map, s_pos, n_ex, n_col);
	s_pos.x = x - 1;
	s_pos.y = y;
	try_reach(map, s_pos, n_ex, n_col);
	s_pos.x = x;
	s_pos.y = y -1;
	try_reach(map, s_pos, n_ex, n_col);
	return ;
}

static t_bool	is_surrended_by_walls(char *map[])
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
	if (validate_content(game) == false)
		return ;
	tmp_matrix = ft_duplicate_char_matrix(game->map);
	try_reach(tmp_matrix, *game->player_position, &exit, &collectibles);
	game->is_map_valid = false;
	if (collectibles != game->collectibles_count)
		game->reason = "Not all collectibles are reachable";
	else if (exit == 0)
		game->reason = "Exit isn't reachable";
	else
		game->is_map_valid = true;
	if (tmp_matrix)
		ft_free_matrix((void **)tmp_matrix);
}
