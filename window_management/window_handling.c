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

int		hook(t_vars *vars);
void	initialize_window(t_vars *vars);

// void my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char *dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

void start_game(t_game *game)
{
	t_vars vars;
	vars.game = game;

	initialize_window(&vars);
	hook(&vars);
	mlx_loop(vars.mlx);
}
//questo metodo non dovrebbe esistere.
//se puoi gestisci i controlli in keyboard handle in base allo stato del gioco,
//questo e' per fare i test e non viene liberato.
int	respawn( int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		end(vars);

	if (keycode == R_KEY)
		printf("the game should restart\n");
	return (0);
}

int	death_animation(t_vars *vars)
{
	static int celframe;

	if (celframe > 1000)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->death_2, 0, 0);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->death_1, 0, 0);

	if (celframe == 2000)
		celframe = 0;
	celframe++;
	return (0);
}

int	death_screen(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	//vars->mlx = mlx_init(); INUTILE DATO CHE MLX È già stata inizializzata
	vars->win = mlx_new_window(vars->mlx, 640, 480, "YOU DIED");
	mlx_key_hook(vars->win, respawn, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, 1L << 0, end, vars);
	mlx_loop_hook(vars->mlx, death_animation, vars);//FA LEAKKARE
	mlx_loop(vars->mlx);
	return (0);
}

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