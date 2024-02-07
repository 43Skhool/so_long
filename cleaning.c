
#include "so_long.h"

//ex window_close
static int	destroy_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	return (0);
}

void	free_game(t_game *game)
{
	if (game->exit_position)
		free(game->exit_position);
	if (game->player_position)
		free(game->player_position);
	if (game->map)
		ft_free_matrix((void **)game->map);
	free(game);
}

static void	free_assets(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->assets->collectible);
	mlx_destroy_image(vars->mlx, vars->assets->exit_closed);
	mlx_destroy_image(vars->mlx, vars->assets->exit_open);
	mlx_destroy_image(vars->mlx, vars->assets->enemy);
	mlx_destroy_image(vars->mlx, vars->assets->wall);
	mlx_destroy_image(vars->mlx, vars->assets->floor);
	mlx_destroy_image(vars->mlx, vars->assets->player_up[0]);
	mlx_destroy_image(vars->mlx, vars->assets->player_up[1]);
	mlx_destroy_image(vars->mlx, vars->assets->player_down[0]);
	mlx_destroy_image(vars->mlx, vars->assets->player_down[1]);
	mlx_destroy_image(vars->mlx, vars->assets->player_right[0]);
	mlx_destroy_image(vars->mlx, vars->assets->player_right[1]);
	mlx_destroy_image(vars->mlx, vars->assets->player_left[0]);
	mlx_destroy_image(vars->mlx, vars->assets->player_left[1]);
	mlx_destroy_image(vars->mlx, vars->assets->death[0]);
	mlx_destroy_image(vars->mlx, vars->assets->death[1]);
	mlx_destroy_image(vars->mlx, vars->assets->win);
	free(vars->assets);
}

int	end(t_vars *vars, t_bool restart)
{
	if (restart == true)
		write(1, "\nRestarting\n\n", 14);
	else
		write(1, "\nGAME END\n", 10);
	free_game(vars->game);
	free_assets(vars);
	destroy_window(vars);
	if (vars->mlx)
		free(vars->mlx);
	if (restart == false)
		exit(0);
	return (1);
}
