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

int		render_next_frame(t_vars *vars);
int		render_tile(t_vars *vars, char type, t_position position);
void	render_movement_count(t_vars *vars, int x, int y);

int	render_next_frame(t_vars *vars)
{
	int			i;
	int			j;
	t_position	position;

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

int	render_player(t_vars *vars, t_position pos, int status)
{
	int	direction;

	direction = vars->game->player_direction;
	if (direction == S_KEY || direction == DOWN_ARROW)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_down[status], pos.x, pos.y);
	else if (direction == W_KEY || direction == UP_ARROW)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_up[status], pos.x, pos.y);
	else if (direction == D_KEY || direction == RIGHT_ARROW)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_right[status], pos.x, pos.y);
	else if (direction == A_KEY || direction == LEFT_ARROW)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player_left[status], pos.x, pos.y);
	return (1);
}

int	render_exit(t_vars *vars, t_position pos)
{
	if (vars->game->collectibles_count != 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->exit_closed, pos.x, pos.y);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->exit_open, pos.x, pos.y);
}

int	render_tile(t_vars *vars, char type, t_position pos)
{
	static int	frame_count;
	int			animation_status;

	if (frame_count > 10000)
		animation_status = 1;
	else
		animation_status = 0;
	if (type == ENEMY)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->enemy, pos.x, pos.y);
	else if (type == PLAYER)
		render_player(vars, pos, animation_status);
	else if (type == COLLECTIBLES)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->collectible, pos.x, pos.y);
	else if (type == FLOOR)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, pos.x, pos.y);
	else if (type == WALL)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->wall, pos.x, pos.y);
	else if (type == EXIT)
		render_exit(vars, pos);
	if (frame_count == 20000)
		frame_count = 0;
	frame_count++;
	return (0);
}

void	render_movement_count(t_vars *vars, int x, int y)
{
	char	*number;

	number = ft_itoa(vars->game->number_of_moves);
	mlx_string_put(vars->mlx, vars->win, x, y, 0XFFFFFF, "Number of moves :");
	mlx_string_put(vars->mlx, vars->win, x + 105, y + 1, 0XFFFFFF, number);
	free(number);
}
