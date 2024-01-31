/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:33:22 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 09:33:34 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_player(void *mlx, void *win, int x, int y) 
{
	int yy = 1;

	while(yy <= 5)
	{
		mlx_pixel_put(mlx, win, x , y + yy, 0xFF0000); // Cor branca
		mlx_pixel_put(mlx, win, x - 1 , y + yy, 0xFF0000); // Cor branca
		mlx_pixel_put(mlx, win, x + 1 , y + yy, 0xFF0000); // Cor branca
		if(yy >= 2 && yy <= 4)
		{
			mlx_pixel_put(mlx, win, x - 2, y + yy, 0xFF0000); // Cor branca
			mlx_pixel_put(mlx, win, x + 2, y + yy, 0xFF0000); // Cor branca
		}
		yy++;
	}
}