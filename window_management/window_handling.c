/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:37:10 by lebartol          #+#    #+#             */
/*   Updated: 2023/12/20 18:18:00 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	hook(t_vars *vars);

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void window_init(t_game *game)
{
	t_vars *vars;
	vars = malloc(sizeof(t_vars));
	vars->game = game;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 400, 400, "So long");

	//mlx_key_hook(vars.win, hook, &vars);
	hook(vars);
	mlx_loop(vars->mlx);
}

int	window_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	return (0);
}

// int render_next_frame(t_vars vars)
// {
// 	return (mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0));
// }

// void draw_line(t_data img, int beginX, int beginY, int endX, int endY, int color)
// {
// 	double deltaX = endX - beginX;
// 	double deltaY = endY - beginY;
// 	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels;
// 	double pixelX = beginX;
// 	double pixelY = beginY;
// 	while (pixels)
// 	{
// 		my_mlx_pixel_put(&img, pixelX, pixelY, color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		--pixels;
// 	}
// }