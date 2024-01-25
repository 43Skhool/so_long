/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:10:55 by marvin            #+#    #+#             */
/*   Updated: 2024/01/25 12:10:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	count_matrix_row(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**duplicate_char_matrix(char **matrix)
{
	int		count_rows;
	int		str_len;
	char	**result;
	int		i;

	count_rows = count_matrix_row(matrix);
	result = malloc(sizeof(char *) * (count_rows + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		str_len = ft_strlen(matrix[i]);
		result[i] = ft_calloc(str_len + 1, sizeof(char));
		ft_strlcpy(result[i], matrix[i], str_len + 1);
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	print_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		write(1, matrix[i], ft_strlen(matrix[i]));
		write(1, "\n", 1);
		i++;
	}
}

//Used for norminette
int	put_img(t_vars *vars, void *asset, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, asset, x, y);
	return (0);
}
