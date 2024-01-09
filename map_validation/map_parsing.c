/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:16:44 by maceccar          #+#    #+#             */
/*   Updated: 2024/01/09 15:16:44 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_game		*validate_map(t_game *game);
static bool	validate_file_name(char *file_name);
static void	read_map(char *file_name, t_game *game);
static bool	get_map_size(char *file_name, t_game *game);
static void	allocate_map(t_game *game);

t_game	*get_map(char *file_name)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->is_map_valid = false;
	if (validate_file_name(file_name) == false)
	{
		game->reason = "Error, wrong file extension";
		return (game);
	}
	if (get_map_size(file_name, game) == false)
	{
		game->reason = "Error, map isn't a rectangle or it is too small";
		return (game);
	}
	read_map(file_name, game);
	if (!game->map)
		return (game->reason = "Error during file read", game);
	validate_map(game);
	if (!game)
		return (game->reason = "Error during map validation", game);
	return (game);
}

// check if file is a '.ber'
static bool	validate_file_name(char *file_name)
{
	char	**file_name_splitted;
	size_t	row_count;
	int		lenght;

	file_name_splitted = ft_split(file_name, '.');
	row_count = count_matrix_row(file_name_splitted);
	lenght = ft_strlen(file_name_splitted[row_count - 1]);
	if (ft_strncmp(file_name_splitted[row_count - 1], "ber", lenght) == 0)
	{
		dealloc_matrix(file_name_splitted);
		return (true);
	}
	dealloc_matrix(file_name_splitted);
	return (false);
}

//map reading from file and check if is a rectangle
static void	read_map(char *file_name, t_game *game)
{
	int		i;
	int		j;
	int		fd;
	char	buffer[1];

	allocate_map(game);
	j = 0;
	i = 0;
	fd = open(file_name, O_RDONLY);
	while (read(fd, buffer, 1) > 0)
	{
		if (*buffer == '\n')
		{
			i++;
			j = 0;
		}
		else if (*buffer != '\r')
		{
			game->map[i][j] = *buffer;
			j++;
		}
	}
	close(fd);
}

static void	allocate_map(t_game *game)
{
	int	i;

	i = 0;
	game->map = ft_calloc(game->number_of_rows + 1, sizeof(char *));
	while (i < game->number_of_rows)
	{
		game->map[i] = ft_calloc(game->number_of_columns + 1, sizeof(char));
		i++;
	}
}

// check if is a rectangle and save the size
static bool	get_map_size(char *file_name, t_game *game)
{
	int			fd;
	char		buffer[1];
	int			n;

	n = 0;
	fd = open(file_name, O_RDONLY);
	game->number_of_rows = 1;
	game->number_of_columns = 0;
	while (read(fd, buffer, sizeof(buffer)) > 0)
	{
		if (*buffer == '\n')
		{
			game->number_of_rows++;
			if (game->number_of_columns != n && game->number_of_columns != 0)
				return (false);
			else
				game->number_of_columns = n;
			n = 0;
		}
		else if (*buffer != '\r')
			n++;
	}
	if (*buffer == '\n' || *buffer == '\r' || game->number_of_columns <= 1)
		return (close(fd), false);
	return (close(fd), true);
}
