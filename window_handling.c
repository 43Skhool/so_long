/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:22:43 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/03 00:47:17 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*get_img(t_vars *vars, char *file);
static void	load_assets(t_vars *vars);
int			hook(t_vars *vars);
void		initialize_window(t_vars *vars);

//Initialize mlx, window
//Start hooking
//mlx_loop: make mlx run
void	start_game(t_game *game)
{
	t_vars	vars;

	vars.game = game;
	vars.mlx = mlx_init();
	if (!vars.mlx)
		end(&vars, false);
	write(1, "\nSTART GAME\n\n", 14);
	initialize_window(&vars);
	hook(&vars);
	mlx_loop(vars.mlx);
}

//Create the mlx window depending on map sized
//Load all the assets
void	initialize_window(t_vars *vars)
{
	int	win_height;
	int	win_width;

	win_height = TILE_SIZE * vars->game->number_of_rows;
	win_width = TILE_SIZE * vars->game->number_of_columns;
	vars->win = mlx_new_window(vars->mlx, win_width, win_height, "So long");
	if (!vars->win)
		end(vars, false);
	load_assets(vars);
}

//Convert all .xpm files in mlx_image
static void	load_assets(t_vars *vars)
{
	vars->assets = malloc(sizeof(t_assets));
	vars->assets->player_up[0] = get_img(vars, "assets/player_up1.xpm");
	vars->assets->player_up[1] = get_img(vars, "assets/player_up2.xpm");
	vars->assets->player_down[0] = get_img(vars, "assets/player_down1.xpm");
	vars->assets->player_down[1] = get_img(vars, "assets/player_down2.xpm");
	vars->assets->player_right[0] = get_img(vars, "assets/player_right1.xpm");
	vars->assets->player_right[1] = get_img(vars, "assets/player_right2.xpm");
	vars->assets->player_left[0] = get_img(vars, "assets/player_left1.xpm");
	vars->assets->player_left[1] = get_img(vars, "assets/player_left2.xpm");
	vars->assets->exit_open = get_img(vars, "assets/exit_open.xpm");
	vars->assets->exit_closed = get_img(vars, "assets/exit_closed.xpm");
	vars->assets->enemy = get_img(vars, "assets/enemy.xpm");
	vars->assets->wall = get_img(vars, "assets/wall.xpm");
	vars->assets->floor = get_img(vars, "assets/floor.xpm");
	vars->assets->collectible = get_img(vars, "assets/collectible.xpm");
	vars->assets->death[0] = get_img(vars, "assets/you_are_dead.xpm");
	vars->assets->death[1] = get_img(vars, "assets/you_are_dead_1.xpm");
	vars->assets->win = get_img(vars, "assets/win.xpm");
}

//Function that actually does the convertion
//	Done beacause of norm
static void	*get_img(t_vars *vars, char *file)
{
	int	w;
	int	h;

	return (mlx_xpm_file_to_image(vars->mlx, file, &w, &h));
}