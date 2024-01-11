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

int	render_next_frame(t_vars *vars);
void	load_assets(t_vars *vars);
int	render_tile(t_vars *vars, char type, t_position position);


void initialize_window(t_vars *vars)
{
	// t_data	img;
	int win_height = TILE_SIZE * vars->game->number_of_rows;
	int win_width = TILE_SIZE * vars->game->number_of_columns;

	vars->mlx = mlx_init();
	if (!vars->mlx)
		end(vars);

	vars->win = mlx_new_window(vars->mlx, win_width, win_height, "So long");
	// img.img = mlx_new_image(vars->mlx, 1920, 1080);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// vars->img = &img;

	if (!vars->win)
		end(vars);

	//TO DO free assets
	load_assets(vars);

	//first render
	//render_next_frame(vars);
}

int	render_next_frame(t_vars *vars)
{
	int			i;
	int			j;
	t_position	position;

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

int	render_tile(t_vars *vars, char type, t_position position)
{
	if (type == ENEMY)
	{
		//mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->enemy, position.x, position.y);
		return (1);
	}

	if (type == PLAYER)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->player, position.x, position.y);
		return (1);
	}

	if (type == COLLECTIBLES)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->collectible, position.x, position.y);
		return (1);
	}

	if (type == FLOOR)
		return (mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y), 1);

	if (type == WALL)
		return (mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->wall, position.x, position.y), 1);

	if (type == EXIT)
	{
		//mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->floor, position.x, position.y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->exit, position.x, position.y);
		return (1);
	}

	return (0);
}

void	load_assets(t_vars *vars)
{
	int img_width;	// dove viene inserita l'altezza che riesce a disegnare
	int img_heigth; // dove viene inserita la larghezza che riesce a disegnare

	vars->assets = malloc(sizeof(t_assets));

	vars->assets->player= mlx_xpm_file_to_image(vars->mlx, "assets/teapot.xpm", &img_width, &img_heigth);
	vars->assets->exit= mlx_xpm_file_to_image(vars->mlx, "assets/exit.xpm", &img_width, &img_heigth);// TO DO da cambiare con un'altro file
	vars->assets->enemy= mlx_xpm_file_to_image(vars->mlx, "assets/mine.xpm", &img_width, &img_heigth);
	vars->assets->wall= mlx_xpm_file_to_image(vars->mlx, "assets/wall_1.xpm", &img_width, &img_heigth);
	vars->assets->floor= mlx_xpm_file_to_image(vars->mlx, "assets/ground.xpm", &img_width, &img_heigth);
	vars->assets->collectible= mlx_xpm_file_to_image(vars->mlx, "assets/collectible.xpm", &img_width, &img_heigth);

	// vars->assets->exit = mlx_xpm_file_to_image(vars->mlx, "../assets/exit.xmp", tmp, tmp);
	// vars->assets->enemy = mlx_xpm_file_to_image(vars->mlx, "../assets/mine.xmp", tmp, tmp);
	// vars->assets->collectible = mlx_xpm_file_to_image(vars->mlx, "../assets/collectible.xmp", tmp, tmp);
	// vars->assets->wall = mlx_xpm_file_to_image(vars->mlx, "../assets/wall_1.xmp", tmp, tmp);
	// vars->assets->floor = mlx_xpm_file_to_image(vars->mlx, "../assets/ground.xmp", tmp, tmp);
}