/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:15:20 by lebartol          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:05 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	render_map(t_vars *vars)
{
	int x = 64;
	vars->data->img = mlx_xpm_file_to_image(vars->mlx, "../assets/ground.xpm", &x, &x);
}

int	render_next_frame(t_vars *vars)
{
	render_map(vars);
	mlx_put_image_to_window(vars->mlx,vars->win,vars->data->img ,0, 0);
	return (0);
}