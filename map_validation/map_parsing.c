/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/24 13:56:23 by maceccar         ###   ########.fr       */
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
	// read_map(file_name, game);
	// if (!game->map)
	// 	return (game->reason = "Error during file reading", game);
	// validate_map(game);
	// if (!game)
	// 	return (game->reason = "Error during map validation", game);
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

//check if is a rectangle and save the size
static t_bool	get_map_size(char *file_name, t_game *game)
{
	int			fd;
	char		buffer[1];
	int			n;

	n = 0;
	fd = open(file_name, O_RDONLY);
	game->number_of_rows = 0;
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
	if (buffer[0] == 4)
		return (close(fd), false);
	if (*buffer == '\n' || *buffer == '\r' || game->number_of_columns <= 1)
		return (close(fd), false);
	return (close(fd), true);
}

//Apro il file
//Leggo una riga
//Finche viene letto qualcosa
//	check lunghezza
//		OK -> avanti
//		NO -> clean e return false
//
//	assegnazione numero di colonne
//	libero buffer attuale
//	leggo la prossima riga
//	aumento il numero di righe
// static t_bool	get_map_size(char *file_name, t_game *game)
// {
// 	char	*buffer;
// 	int		fd;

// 	fd = open(file_name, O_RDONLY);
// 	buffer = get_next_line(fd, false);
// 	while (buffer && ft_strlen(buffer) > 0)
// 	{
// 		if (ft_strlen(buffer) != game->number_of_columns && game->number_of_columns != 0)
// 		{
// 			get_next_line(fd, true);
// 			free(buffer);
// 			close(fd); 
// 			return (false);
// 		}
// 		game->number_of_columns = ft_strlen(buffer);

// 		free(buffer);
// 		buffer = get_next_line(fd, false);
// 		game->number_of_rows++;
// 	}

// 	get_next_line(fd, true);
// 	free(buffer);
// 	close(fd);
// 	return (true);
// }