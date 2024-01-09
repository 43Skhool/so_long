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
void init_window(t_vars *vars)
{
	t_data	img;
	int height = TILE_SIZE * vars->game->number_of_rows;
	int width = TILE_SIZE * vars->game->number_of_columns;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		end(vars);
	vars->win = mlx_new_window(vars->mlx, width, height, "So long");
	if (!vars->win)
		end(vars);

	img.img = mlx_new_image(vars->mlx, width, height);
	img.addr =mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	vars->data = &img;
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}
void start_game(t_game *game)
{
	t_vars vars;
	vars.game = game;

	init_window(&vars);
	hook(&vars);
	mlx_loop(vars.mlx);
}

int render_next_frame(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	return (0);
}

void draw_line(t_data img, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(&img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}