
#include "so_long.h"

//Used for norminette
int	put_img(t_vars *vars, void *asset, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, asset, x, y);
	return (0);
}

//Return tre in case of allocation failed
t_game	*allocate_game(t_game *game)
{
	game = malloc(sizeof(t_game));
	if (!game)
		return (game);
	game->player_direction = DOWN_ARROW;
	game->number_of_moves = 0;
	game->is_map_valid = false;
	game->map = NULL;
	game->player_position = NULL;
	game->exit_position = NULL;
	return (game);
}
