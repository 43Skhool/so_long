/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:50:38 by maceccar          #+#    #+#             */
/*   Updated: 2024/05/03 00:50:38 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_enemy(t_vars *vars, int x, int y);
static void	try_move_enemy(t_vars *vars, t_position init, int end_x, int end_y);

//Each 1000 frame, the enemy moves
//	1000 beacase are 500(0-500) + 500(1000)
//	500: after 500 frame from the start of the game the enemy moves
//	1000: each 1000 frame, the count restart form 0
//frame_count is static so it can store his value throw the calls
//	Beacause it increment each call of this function
//Each enemy in the map moves
int	enemy_movement(t_vars *vars)
{
	static int	frame_count;
	int			i;
	int			j;

	if (frame_count == 500)
	{
		i = 0;
		while (vars->game->map[i])
		{
			j = 0;
			while (vars->game->map[i][j])
			{
				if (vars->game->map[i][j] == ENEMY)
					move_enemy(vars, i, j);
				j++;
			}
			i++;
		}
	}
	if (frame_count == 1000)
		frame_count = 0;
	frame_count++;
	return (1);
}

//Extract a random number using 'rand' function
//	get the module 4 of random number and switch the result
//	the new position of the enemy will depend by this number
//0 => UP
//1 => RIGHT
//2 => DOWN
//3 => LEFT
static void	move_enemy(t_vars *vars, int x, int y)
{
	int			rndm_nmb;
	t_position	start;

	start.x = x;
	start.y = y;
	rndm_nmb = rand() % 4;
	if (rndm_nmb == 0)
		try_move_enemy(vars, start, x, y - 1);
	if (rndm_nmb == 1)
		try_move_enemy(vars, start, x + 1, y);
	if (rndm_nmb == 2)
		try_move_enemy(vars, start, x, y + 1);
	if (rndm_nmb == 3)
		try_move_enemy(vars, start, x - 1, y);
}

//If ther's the player, kill it => the game ends
//If ther's an empty tile, just switch the position
static void	try_move_enemy(t_vars *vars, t_position init, int end_x, int end_y)
{
	if (vars->game->map[end_x][end_y] == PLAYER)
		finish_game(vars, lose);
	if (vars->game->map[end_x][end_y] == FLOOR)
	{
		vars->game->map[end_x][end_y] = ENEMY;
		vars->game->map[init.x][init.y] = FLOOR;
	}
}
