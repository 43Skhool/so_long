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

int handle_input(int keysym, t_game *game, t_vars *vars)
{
	if (keysym == KEY_ESC)
	{
        printf("\nThe %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(vars->mlx, vars->win);
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);

		return (0);
	}

	game_status status = move(game, keysym);
	print_char_matrix(game->map);
	printf("\n");

	if (status == win)
		printf("|win|\n");

	if (status == lose)
		printf("|lost|\n");

	if (status == win || status == lose)
		return (1);
	return (0);
}
