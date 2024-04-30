/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:14 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_game			*validate_map(t_game *game);
t_game			*allocate_game(t_game *game);
static t_bool	validate_file_name(char *file_name, t_game *game);
static void		read_map(char *file_name, t_game *game);
static t_bool	get_map_size(char *file_name, t_game *game);
static void		allocate_map(t_game *game);

t_game	*get_map(char *file_name)
{
	t_game	*game;

	game = allocate_game(game);
	if (!game)
		return (NULL);
	if (validate_file_name(file_name, game) == false)
		return (game);
	if (get_map_size(file_name, game) == false)
	{
		game->reason = "Error, map isn't a rectangle or it is too small";
		return (game);
	}
	read_map(file_name, game);
	if (!game->map)
		return (game->reason = "Error during file reading", game);
	validate_map(game);
	if (!game)
		return (game->reason = "Error during map validation", game);
	game->file = file_name;
	return (game);
}

// check if file is a '.ber'
static t_bool	validate_file_name(char *file_name, t_game *game)
{
	char	**file_name_splitted;
	size_t	row_count;
	int		lenght;
	int		fd;

	file_name_splitted = ft_split(file_name, '.');
	row_count = ft_count_matrix_row((void **)file_name_splitted);
	lenght = ft_strlen(file_name_splitted[row_count - 1]);
	if (ft_strncmp(file_name_splitted[row_count - 1], "ber", lenght) == 0)
	{
		ft_free_matrix((void **)file_name_splitted);
		fd = open(file_name, O_RDONLY);
		if (fd == -1)
			return (game->reason = "Error, file not found", false);
		close (fd);
		return (true);
	}
	ft_free_matrix((void **)file_name_splitted);
	return (game->reason = "Error, wring file extension", false);
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

static t_bool	get_map_size(char *file_name, t_game *game)
{
	char	*buffer;
	int		fd;
	t_bool	result;
	int		line_length;

	result = true;
	fd = open(file_name, O_RDONLY);
	while (buffer = get_next_line(fd, false))
	{
		line_length = ft_strlen(buffer);
		if (line_length != game->number_of_columns && game->number_of_columns != 0)
		{
			free(buffer);
			result = false;
			break;
		}
		game->number_of_columns = line_length;

		game->number_of_rows++;
		free(buffer);
	}

	get_next_line(fd, true);
	close(fd);
	if (game->number_of_rows <= 2)
		result = false;
	return (result);
}
