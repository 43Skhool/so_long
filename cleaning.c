#include "so_long.h"

//ex window_close
static int	destroy_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	return (0);
}

void	dealloc_matrix(char **matrix)
{
	if (!matrix)
		return ;
	int i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void free_game(t_game *game)
{
	if (game->exit_position)
		free(game->exit_position);
	if (game->player_position)
		free(game->player_position);
	dealloc_matrix(game->map);
	free(game);
}

void free_assets(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->assets->collectible);
	mlx_destroy_image(vars->mlx, vars->assets->exit);
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

	//TO DO da cambiare quando saranno in un vettore
	mlx_destroy_image(vars->mlx, vars->assets->win_1);
	mlx_destroy_image(vars->mlx, vars->assets->win_2);

	free(vars->assets);
}

int end(t_vars *vars, bool restart)
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
