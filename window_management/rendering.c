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
void render_movement_count(t_vars *vars, int x, int y);

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
	render_movement_count(vars, 10, 20);
	return (0);
}

int render_player(t_vars *vars, t_position position/*, int animation_status*/)
{
	// int direction = vars->game->player_direction;
 	// if (direction == W_KEY || direction == UP_ARROW)
	// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_up[animation_status], position.x, position.y);
	// else if (direction == S_KEY || direction == DOWN_ARROW)
	// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_down[animation_status], position.x, position.y);
	// else if (direction == D_KEY || direction == RIGHT_ARROW)
	// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_right[animation_status], position.x, position.y);
	// else if (direction == A_KEY || direction == LEFT_ARROW)
	// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_left[animation_status], position.x, position.y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_up[1], position.x, position.y);
	return (1);
}

int render_tile(t_vars *vars, char type, t_position position)
{
	static int frame_count;
	// int	animation_status;

	// if (frame_count > 30)
	// 	animation_status = 1;
	// else
	// 	animation_status = 0;

	if (type == ENEMY)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->enemy, position.x, position.y);
	else if (type == PLAYER)
		render_player(vars, position/*, animation_status*/);
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

void render_movement_count(t_vars *vars, int x, int y)
{
	char *number =  ft_itoa(vars->game->number_of_moves);
	mlx_string_put(vars->mlx, vars->win, x, y, 0XFFFFFF, "Number of moves :");
	mlx_string_put(vars->mlx, vars->win, x + 105, y + 1, 0XFFFFFF, number);

	free(number);
}