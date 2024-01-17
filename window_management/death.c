#include "../so_long.h"

//questo metodo non dovrebbe esistere.
//se puoi gestisci i controlli in keyboard handle in base allo stato del gioco,
//questo e' per fare i test e non viene liberato.

void	initialize_window(t_vars *vars);
int		hook(t_vars *vars);

int	respawn( int keycode, t_vars *vars)
{
	t_game *game;

	if (keycode == KEY_ESC)
		end(vars, false);

	if (keycode == R_KEY)
	{
		char *file_tmp = vars->game->file;
		end(vars, true);
		t_game *game = get_map(file_tmp);
		game->file = file_tmp;
		start_game(game);
	}
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

int	death(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	//vars->mlx = mlx_init(); INUTILE DATO CHE MLX È già stata inizializzata, è quello che faceva leakkare
	vars->win = mlx_new_window(vars->mlx, 640, 480, "YOU DIED");
	mlx_key_hook(vars->win, respawn, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, 1L << 0, end, vars);
	mlx_loop_hook(vars->mlx, death_animation, vars);//FA LEAKKARE
	mlx_loop(vars->mlx);
	return (0);
}