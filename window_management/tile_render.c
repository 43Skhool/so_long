/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:15:20 by lebartol          #+#    #+#             */
/*   Updated: 2024/01/11 13:28:15 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	render_map(t_vars *vars)
{
	int x = 64;
	vars->img->img = mlx_xpm_file_to_image(vars->mlx, "../assets/ground.xpm", &x, &x);
}