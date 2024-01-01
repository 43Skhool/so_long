/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:53:28 by lebartol          #+#    #+#             */
/*   Updated: 2023/12/20 18:21:00 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook(t_vars vars, t_data img)
{
	mlx_key_hook(vars.win, keyboard_handler, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, DESTROY_NOTIFY, 0, window_close, &vars);
	mlx_loop_hook(mlx, render_next_frame, img, &vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("keyboard input: %d\n", keycode);
	if (keycode == KEY_ESC)
		window_close(keycode, vars);
	return (0);
}

int mouse_hook(int mouse, t_vars *vars)
{
	printf(" %d mouse event %d\n", mouse);
	return(0);
}

int keyboard_handler(t_data *vars)
{

}