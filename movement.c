#include "so_long.h"
//sarebbe da fare tipo una maschera per gestire tutti i tipi di input con un solo tipo
//dato che ci sono sia i wasd che le freccie, per ora sono gestiti entrambi

static bool try_move(game *game, position newposition);
static void switch_position(game *game, position newposition);

bool move(game *game, int direction)
{
	position newposition;
	newposition = *game->player_position;

	//SU
	if (direction == W_KEY || direction == UP_ARROW)
		return (newposition.x--, try_move(game, newposition));

	//GIÚ
	if (direction == S_KEY || direction == DOWN_ARROW)
		return (newposition.x++, try_move(game, newposition));

	//DESTRA
	if (direction == D_KEY || direction == RIGHT_ARROW)
		return (newposition.y++, try_move(game, newposition));

	//SINISTRA
	if (direction == A_KEY || direction == LEFT_ARROW)
		return (newposition.x++, try_move(game, newposition));

	return (false);
}

static bool try_move(game *game, position newposition)
{
	//WALL
	if (game->map[newposition.x][newposition.y] == WALL)
		return (false);

	//COLLECTIBLE
	if (game->map[newposition.x][newposition.y] == COLLECTIBLES)
		game->collectibles_count--;

	switch_position(game, newposition);
	return (true);
}

static void switch_position(game *game, position newposition)
{
	game->map[newposition.x][newposition.y] = 'P';
	game->map[game->player_position->x][game->player_position->y] = '0';
	game->player_position->x = newposition.x;
	game->player_position->y = newposition.y;
}

