/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:15:20 by lebartol          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:05 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int render_next_frame(t_vars *vars);
void load_assets(t_vars *vars);
int render_tile(t_vars *vars, char type, t_position position);

void initialize_window(t_vars *vars)
{
	int win_height = TILE_SIZE * vars->game->number_of_rows;
	int win_width = TILE_SIZE * vars->game->number_of_columns;

	vars->mlx = mlx_init();
	if (!vars->mlx)
		end(vars);

	vars->win = mlx_new_window(vars->mlx, win_width, win_height, "So long");

	if (!vars->win)
		end(vars);

	load_assets(vars);
}

int render_next_frame(t_vars *vars)
{
	int i;
	int j;
	t_position position;

	i = 0;
	j = 0;
	while (i < vars->game->number_of_rows)
	{
		j = 0;
		while (j < vars->game->number_of_columns)
		{
			position.x = j * TILE_SIZE;
			position.y = i * TILE_SIZE;
			render_tile(vars, vars->game->map[i][j], position);
			j++;
		}
		i++;
	}
	return (0);
}

int render_tile(t_vars *vars, char type, t_position position)
{
	static int frame_count;
	int	anitmation_status;

	if (frame_count > 30)
		anitmation_status = 1;
	else
		anitmation_status = 0;

	if (type == ENEMY)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->enemy, position.x, position.y);
	else if (type == PLAYER)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player[anitmation_status], position.x, position.y);
	else if (type == COLLECTIBLES)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->collectible, position.x, position.y);
	else if (type == FLOOR)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y);
	else if (type == WALL)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->wall, position.x, position.y);
	else if (type == EXIT)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->exit, position.x, position.y);

	if (frame_count == 60)
		frame_count = 0;

	frame_count++;

	return (0);
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