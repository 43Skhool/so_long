#include "../so_long.h"

void	initialize_window(t_vars *vars);
int		hook(t_vars *vars);
int		destroy_notify(t_vars *vars);

int	finish_hook( int keycode, t_vars *vars)
{
	t_game	*game;

	if (keycode == KEY_ESC)
		end(vars, false);
	//
	if (keycode == R_KEY)
	{
		char *file_tmp = vars->game->file;
		end(vars, true);
		game = get_map(file_tmp);
		start_game(game);
	}
	return (0);
}

int	death_animation(t_vars *vars)
{
	static int celframe;
	//
	if (celframe > 1000)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->death[0], 0, 0);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->death[1], 0, 0);

	if (celframe == 2000)
		celframe = 0;
	celframe++;
	return (0);
}

int	win_animation(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->assets->win, 0, 0);
	return (0);
}

int	finish_game(t_vars *vars, game_status status)
{
	mlx_destroy_window(vars->mlx, vars->win);
	//
	if (status == lose)
	{
		vars->win = mlx_new_window(vars->mlx, 640, 480, "YOU DIED");
		write(1, "\nLOSE\n\n", 6);

	}
	else if (status == win)
	{
		vars->win = mlx_new_window(vars->mlx, 640, 480, "YOU WIN");
		write(1, "\nWIN\n\n", 5);
	}
	//
	mlx_key_hook(vars->win, finish_hook, vars);
	//
	mlx_hook(vars->win, DESTROY_NOTIFY, 1L << 0, destroy_notify, vars);
	//
	if (status == lose)
		mlx_loop_hook(vars->mlx, death_animation, vars);
	else if (status == win)
		mlx_loop_hook(vars->mlx, win_animation, vars);
	//
	mlx_loop(vars->mlx);
	//
	return (0);
}