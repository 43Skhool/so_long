/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/05/28 13:05:29 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	render_player(t_vars *vars, t_position pos, int status)
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

static void	render_movement_count(t_vars *vars, int x, int y)
{
	char	*number;

	number = ft_itoa(vars->game->number_of_moves);
	mlx_string_put(vars->mlx, vars->win, x, y, 0XFFFFFF, "Number of moves :");
	mlx_string_put(vars->mlx, vars->win, x + 105, y, 0XFFFFFF, number);
	free(number);
}

static int	render_exit(t_vars *vars, t_position pos)
{
	if (vars->game->collectibles_count != 0)
		put_img(vars, vars->assets->exit_closed, pos.x, pos.y);
	else
		put_img(vars, vars->assets->exit_open, pos.x, pos.y);
	return (0);
}

static int	render_tile(t_vars *vars, int j, int i, int as)
{
	t_position	pos;
	char		type;

	type = vars->game->map[i][j];
	pos.x = j * TILE_SIZE;
	pos.y = i * TILE_SIZE;
	if (type == ENEMY)
		put_img(vars, vars->assets->enemy, pos.x, pos.y);
	else if (type == PLAYER)
		render_player(vars, pos, as);
	else if (type == COLLECTIBLES)
		put_img(vars, vars->assets->collectible, pos.x, pos.y);
	else if (type == FLOOR)
		put_img(vars, vars->assets->floor, pos.x, pos.y);
	else if (type == WALL)
		put_img(vars, vars->assets->wall, pos.x, pos.y);
	else if (type == EXIT)
		render_exit(vars, pos);
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	static int	ms;
	int			anim_status;
	int			i;
	int			j;

	anim_status = (ms > 500);
	if (ms > 1000)
		ms = 0;
	enemy_movement(vars);
	i = 0;
	j = 0;
	while (i < vars->game->number_of_rows)
	{
		j = 0;
		while (j < vars->game->number_of_columns)
		{
			render_tile(vars,j , i, anim_status);
			j++;
		}
		i++;
	}
	render_movement_count(vars, 10, 20);
	usleep(100);
	ms++;
	return (0);
}
