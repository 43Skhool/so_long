/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/05/20 17:34:03 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_keyboard_input(int keysym, t_vars *vars)
{
	t_game_status	status;

	if (keysym == KEY_ESC)
		end(vars, false);
	status = move(vars->game, keysym);
	if (status == moved)
	{
		vars->game->number_of_moves++;
		write(1, "Movement count: ", 16);
		ft_putnbr_fd(vars->game->number_of_moves, 1);
		write(1, "\r\n", 1);
	}
	if (status == win || status == lose)
		finish_game(vars, status);
	return (0);
}

int	destroy_notify(t_vars *vars)
{
	end(vars, false);
	return (1);
}

int	hook(t_vars *vars)
{
	mlx_key_hook(vars->win, handle_keyboard_input, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, 1L << 0, destroy_notify, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	return (0);
}
