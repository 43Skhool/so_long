/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:15:20 by lebartol          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:05 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int render_next_frame(t_vars *vars);
int render_tile(t_vars *vars, char type, t_position position);

int render_next_frame(t_vars *vars)
{
	int i;
	int j;
	t_position position;

	i = 0;
	j = 0;
	while (i < vars->game->number_of_rows)
	{
		j = 0;
		while (j < vars->game->number_of_columns)
		{
			position.x = j * TILE_SIZE;
			position.y = i * TILE_SIZE;
			render_tile(vars, vars->game->map[i][j], position);
			j++;
		}
		i++;
	}
	return (0);
}

int render_tile(t_vars *vars, char type, t_position position)
{
	static int frame_count;
	int	anitmation_status;

	if (frame_count > 30)
		anitmation_status = 1;
	else
		anitmation_status = 0;

	if (type == ENEMY)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->enemy, position.x, position.y);
	else if (type == PLAYER)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player[anitmation_status], position.x, position.y);
	else if (type == COLLECTIBLES)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->collectible, position.x, position.y);
	else if (type == FLOOR)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y);
	else if (type == WALL)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->wall, position.x, position.y);
	else if (type == EXIT)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->exit, position.x, position.y);

	if (frame_count == 60)
		frame_count = 0;

	frame_count++;

	return (0);
}