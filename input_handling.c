/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:53:28 by lebartol          #+#    #+#             */
/*   Updated: 2023/12/28 18:11:36 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_vars *vars)
{
		//validate_move( player_position + 1y );
		vars->map.player_position->y -= 10;
}

void	move_down(t_vars *vars)
{
		//validate_move( player_position - 1y );
		vars->map.player_position->y += 10;
}

void	move_left(t_vars *vars)
{
		//validate_move( player_position - 1x );
		vars->map.player_position->x -= 10;
}

void	move_right(t_vars *vars)
{
		//validate_move( player_position + 1x );
		vars->map.player_position->x += 10;
}

int	keyboard_handler(int keycode, t_vars *vars)
{
	printf("keyboard input: %d\n", keycode);
	printf("p: [%d, %d]\n", vars->map.player_position->x, vars->map.player_position->y);
	if (keycode == KEY_ESC)
		window_close(vars);
	else if (keycode == W_KEY || keycode == UP_ARROW)
			move_up(vars);
	else if (keycode == S_KEY || keycode == DOWN_ARROW)
			move_down(vars);
	else if (keycode == A_KEY || keycode == LEFT_ARROW)
			move_left(vars);
	else if (keycode == D_KEY || keycode == RIGHT_ARROW)
			move_right(vars);
	return (0);
}

void	hook(t_vars *vars)
{
	mlx_key_hook(vars->win, keyboard_handler, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, 0, window_close, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
}