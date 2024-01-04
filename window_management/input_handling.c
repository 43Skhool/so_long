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

static int handle_input(int keysym, t_vars *vars);

int	hook(t_vars *vars)
{
	mlx_key_hook(vars->win, handle_input, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, 1L << 0, window_close, vars);
	//mlx_hook(vars->win, 2, 1L<<0, window_close, vars);
	//mlx_loop_hook(vars->mlx, render_next_frame, &vars);
	return (0);
}

static int handle_input(int keysym, t_vars *vars)
{
	if (keysym == KEY_ESC)
	{
        printf("\nThe %d key (ESC) has been pressed\n\n", keysym);
		window_close(vars);

		exit(0);
	}

	game_status status = move(vars->game, keysym);
	print_char_matrix(vars->game->map);
	printf("\n");

	if (status == win)
		printf("|win|\n");

	if (status == lose)
		printf("|lost|\n");

	if (status == win || status == lose)
		return (1);
	return (0);
}
