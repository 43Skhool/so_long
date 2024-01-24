#include "so_long.h"

int main(int argc, char *argv[])
{
	t_game *game;
	if (argc != 2)
	{
		write(1, "Error, Specify a map file\n", 26);
		return (0);
	}
	game = get_map(argv[1]);
	if (!game)
		write(1, "Error, allocation failed\n", 25);
	if (game->is_map_valid == false)
	{
		write(1, game->reason, ft_strlen(game->reason));
		write(1, "\n", 1);
	}
	else
		start_game(game);
	free_game(game);
}
