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

void start_game(t_game *game)
{
	t_vars vars;
	vars.game = game;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		end(&vars, false);

	write(1, "\nSTART GAME\n\n", 14);

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

	vars->assets->player_up[0] = mlx_xpm_file_to_image(vars->mlx, "assets/player_up_idle_1.xpm", &img_width, &img_heigth);
	vars->assets->player_up[1] = mlx_xpm_file_to_image(vars->mlx, "assets/player_up_idle_2.xpm", &img_width, &img_heigth);

	vars->assets->player_down[0] = mlx_xpm_file_to_image(vars->mlx, "assets/player_down_idle_1.xpm", &img_width, &img_heigth);
	vars->assets->player_down[1] = mlx_xpm_file_to_image(vars->mlx, "assets/player_down_idle_2.xpm", &img_width, &img_heigth);

	vars->assets->player_right[0] = mlx_xpm_file_to_image(vars->mlx, "assets/player_right_idle_1.xpm", &img_width, &img_heigth);
	vars->assets->player_right[1] = mlx_xpm_file_to_image(vars->mlx, "assets/player_right_idle_2.xpm", &img_width, &img_heigth);

	vars->assets->player_left[0] = mlx_xpm_file_to_image(vars->mlx, "assets/player_left_idle_1.xpm", &img_width, &img_heigth);
	vars->assets->player_left[1] = mlx_xpm_file_to_image(vars->mlx, "assets/player_left_idle_2.xpm", &img_width, &img_heigth);

	vars->assets->exit_open = mlx_xpm_file_to_image(vars->mlx, "assets/exit_open.xpm", &img_width, &img_heigth); // TO DO da cambiare con un'altro file
	vars->assets->exit_closed = mlx_xpm_file_to_image(vars->mlx, "assets/exit_closed.xpm", &img_width, &img_heigth); // TO DO da cambiare con un'altro file
	vars->assets->enemy = mlx_xpm_file_to_image(vars->mlx, "assets/enemy.xpm", &img_width, &img_heigth);
	vars->assets->wall = mlx_xpm_file_to_image(vars->mlx, "assets/wall.xpm", &img_width, &img_heigth);
	vars->assets->floor = mlx_xpm_file_to_image(vars->mlx, "assets/floor.xpm", &img_width, &img_heigth);
	vars->assets->collectible = mlx_xpm_file_to_image(vars->mlx, "assets/collectible.xpm", &img_width, &img_heigth);

	vars->assets->death[0] = mlx_xpm_file_to_image(vars->mlx, "assets/you_are_dead.xpm", &img_width, &img_heigth);
	vars->assets->death[1] = mlx_xpm_file_to_image(vars->mlx, "assets/you_are_dead_1.xpm", &img_width, &img_heigth);

	//TO DO da cambiare asset e mettere nel vettore
	vars->assets->win = mlx_xpm_file_to_image(vars->mlx, "assets/win.xpm", &img_width, &img_heigth);
}