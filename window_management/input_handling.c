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

void	hook(t_vars *vars)
{
	mlx_key_hook(vars->win, keyboard_handler, &vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, 0, window_close, &vars);
	mlx_loop_hook(vars->mlx, render_next_frame, &vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("keyboard input: %d\n", keycode);
	if (keycode == KEY_ESC)
		window_close(keycode, vars);
	return (0);
}

int keyboard_handler(int key_code, t_vars *vars)
{
//dovremmo mettere un offset di TILE_SIZE a posizione o inserirlo nella casella corrispondente nel momento della scrittura dell'immagine?
	if (key_code == KEY_ESC)
		return (window_close(key_code, vars));

	move(vars->game, key_code);


	return (false);
}