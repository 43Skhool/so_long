/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:14 by maceccar         ###   ########.fr       */
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
		put_img(vars, vars->assets->player_down[status], pos.x, pos.y);
	else if (direction == W_KEY || direction == UP_ARROW)
		put_img(vars, vars->assets->player_up[status], pos.x, pos.y);
	else if (direction == D_KEY || direction == RIGHT_ARROW)
		put_img(vars, vars->assets->player_right[status], pos.x, pos.y);
	else if (direction == A_KEY || direction == LEFT_ARROW)
		put_img(vars, vars->assets->player_left[status], pos.x, pos.y);
	return (1);
}

int	render_exit(t_vars *vars, t_position pos)
{
	if (vars->game->collectibles_count != 0)
		put_img(vars, vars->assets->exit_closed, pos.x, pos.y);
	else
		put_img(vars, vars->assets->exit_open, pos.x, pos.y);
	return (0);
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
		put_img(vars, vars->assets->enemy, pos.x, pos.y);
	else if (type == PLAYER)
		render_player(vars, pos, animation_status);
	else if (type == COLLECTIBLES)
		put_img(vars, vars->assets->collectible, pos.x, pos.y);
	else if (type == FLOOR)
		put_img(vars, vars->assets->floor, pos.x, pos.y);
	else if (type == WALL)
		put_img(vars, vars->assets->wall, pos.x, pos.y);
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
	g_put(vars->mlx, vars->win, x, y, 0XFFFFFF, "Number of moves :");
	mlx_string_put(vars->mlx, vars->win, x + 105, y + 1, 0XFFFFFF, number);
	free(number);
}
