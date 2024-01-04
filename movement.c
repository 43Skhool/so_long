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

	// SU
	if (direction == W_KEY || direction == UP_ARROW)
		return (newposition.x--, try_move(game, newposition));

	// GIÚ
	if (direction == S_KEY || direction == DOWN_ARROW)
		return (newposition.x++, try_move(game, newposition));

	// DESTRA
	if (direction == D_KEY || direction == RIGHT_ARROW)
		return (newposition.y++, try_move(game, newposition));

	// SINISTRA
	if (direction == A_KEY || direction == LEFT_ARROW)
		return (newposition.y--, try_move(game, newposition));

	return (playing);
}

static game_status try_move(t_game *game, t_position newposition)
{
	// WALL
	if (game->map[newposition.x][newposition.y] == WALL)
		return (playing);

	// COLLECTIBLE
	if (game->map[newposition.x][newposition.y] == COLLECTIBLES)
		game->collectibles_count--;

	return (switch_position(game, newposition));
}

// se arriva alla fine e tutto i collectibles sono stati presi -> return true
static game_status switch_position(t_game *game, t_position newposition)
{
	game_status status;

	status = playing;
	//'Arrivando' nella posizione dell'uscita
	if (game->map[newposition.x][newposition.y] == 'E' && game->collectibles_count == 0)
		status = win;

	//trovato un nemico
	if (game->map[newposition.x][newposition.y] == 'M')
		status = lose;

	game->map[newposition.x][newposition.y] = 'P';

	//'Uscendo' dalla posizione dell'uscita, il valore nella cella dove era il player deve tornare ad essere 'E'
	if (game->exit_position->x == game->player_position->x && game->exit_position->y == game->player_position->y)
		game->map[game->player_position->x][game->player_position->y] = 'E';
	else
		game->map[game->player_position->x][game->player_position->y] = '0';

	game->player_position->x = newposition.x;
	game->player_position->y = newposition.y;

	return (status);
}