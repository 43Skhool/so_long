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

int end(t_vars *vars)
{
	free_game(vars->game);
	destroy_window(vars);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
}
