/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling->c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:53:28 by lebartol          #+#    #+#             */
/*   Updated: 2023/12/20 18:21:00 by lebartol         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int handle_keyboard_input(int keysym, t_vars *vars);
int	finish_game(t_vars *vars, game_status status);

int	hook(t_vars *vars)
{
	mlx_key_hook(vars->win, handle_keyboard_input, vars);
	//mlx_hook(vars->win, 04, (1L<<2), handle_keyboard_input, vars);inutile dato che credo venga gestito a prescindere
	mlx_hook(vars->win, DESTROY_NOTIFY, 1L << 0, end, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	return (0);
}

static int handle_keyboard_input(int keysym, t_vars *vars)
{
	game_status status;
	if (keysym == KEY_ESC)
		end(vars, false);

	status = move(vars->game, keysym);

	if (status == win || status == lose)
		finish_game(vars, status);

	return (0);
}