#include "so_long.h"
// sarebbe da fare tipo una maschera per gestire tutti i tipi di input con un solo tipo
// dato che ci sono sia i wasd che le freccie, per ora sono gestiti entrambi

static game_status try_move(t_game *game, t_position newposition);
static game_status switch_position(t_game *game, t_position newposition);

// return false if the game can keep go on, returno true if the game is ended
game_status move(t_game *game, int direction)
{
	t_position newposition;
	newposition = *game->player_position;

	if (direction == W_KEY || direction == UP_ARROW)
	{
		//game->player_direction = direction;
		return (newposition.x--, try_move(game, newposition));
	}
	if (direction == S_KEY || direction == DOWN_ARROW)
	{
		//game->player_direction = direction;
		return (newposition.x++, try_move(game, newposition));
	}
	if (direction == D_KEY || direction == RIGHT_ARROW)
	{
		//game->player_direction = direction;
		return (newposition.y++, try_move(game, newposition));
	}
	if (direction == A_KEY || direction == LEFT_ARROW)
	{
		//game->player_direction = direction;
		return (newposition.y--, try_move(game, newposition));
	}
	return (playing);
}

static game_status	try_move(t_game *game, t_position newposition)
{
	if (game->map[newposition.x][newposition.y] == WALL)
		return (playing);
	if (game->map[newposition.x][newposition.y] == COLLECTIBLES)
		game->collectibles_count--;
	return (switch_position(game, newposition));
}

// se arriva alla fine e tutto i collectibles sono stati presi -> return true
static game_status	switch_position(t_game *game, t_position newposition)
{
	game_status status;

	status = moved;
	if (game->map[newposition.x][newposition.y] == 'E' && game->collectibles_count == 0)
		status = win;
	if (game->map[newposition.x][newposition.y] == 'M')
		status = lose;
	game->map[newposition.x][newposition.y] = 'P';
	if (game->exit_position->x == game->player_position->x && game->exit_position->y == game->player_position->y)
		game->map[game->player_position->x][game->player_position->y] = 'E';
	else
		game->map[game->player_position->x][game->player_position->y] = '0';
	game->player_position->x = newposition.x;
	game->player_position->y = newposition.y;
	return (status);
}
