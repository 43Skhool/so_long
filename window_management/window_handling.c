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
void	load_assets(t_vars *vars);
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

	vars.mlx = mlx_init();
	if (!vars.mlx)
		end(&vars, false);

	initialize_window(&vars);
	hook(&vars);
	mlx_loop(vars.mlx);
}

void initialize_window(t_vars *vars)
{
	int win_height = TILE_SIZE * vars->game->number_of_rows;
	int win_width = TILE_SIZE * vars->game->number_of_columns;

	vars->win = mlx_new_window(vars->mlx, win_width, win_height, "So long");

	if (!vars->win)
		end(vars, false);

	load_assets(vars);
}

void load_assets(t_vars *vars)
{
	int img_width;	// dove viene inserita l'altezza che riesce a disegnare
	int img_heigth; // dove viene inserita la larghezza che riesce a disegnare

	vars->assets = malloc(sizeof(t_assets));

	vars->assets->player[0] = mlx_xpm_file_to_image(vars->mlx, "assets/teapot.xpm", &img_width, &img_heigth);
	vars->assets->player[1] = mlx_xpm_file_to_image(vars->mlx, "assets/exit.xpm", &img_width, &img_heigth);

	vars->assets->exit = mlx_xpm_file_to_image(vars->mlx, "assets/exit.xpm", &img_width, &img_heigth); // TO DO da cambiare con un'altro file
	vars->assets->enemy = mlx_xpm_file_to_image(vars->mlx, "assets/mine.xpm", &img_width, &img_heigth);
	vars->assets->wall = mlx_xpm_file_to_image(vars->mlx, "assets/wall_1.xpm", &img_width, &img_heigth);
	vars->assets->floor = mlx_xpm_file_to_image(vars->mlx, "assets/ground.xpm", &img_width, &img_heigth);
	vars->assets->collectible = mlx_xpm_file_to_image(vars->mlx, "assets/collectible.xpm", &img_width, &img_heigth);
	// DA ELIMINARE
	vars->assets->death_1 = mlx_xpm_file_to_image(vars->mlx, "assets/you_are_dead.xpm", &img_width, &img_heigth);
	vars->assets->death_2 = mlx_xpm_file_to_image(vars->mlx, "assets/you_are_dead_1.xpm", &img_width, &img_heigth);

	// vars->assets->exit = mlx_xpm_file_to_image(vars->mlx, "../assets/exit.xmp", tmp, tmp);
	// vars->assets->enemy = mlx_xpm_file_to_image(vars->mlx, "../assets/mine.xmp", tmp, tmp);
	// vars->assets->collectible = mlx_xpm_file_to_image(vars->mlx, "../assets/collectible.xmp", tmp, tmp);
	// vars->assets->wall = mlx_xpm_file_to_image(vars->mlx, "../assets/wall_1.xmp", tmp, tmp);
	// vars->assets->floor = mlx_xpm_file_to_image(vars->mlx, "../assets/ground.xmp", tmp, tmp);
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