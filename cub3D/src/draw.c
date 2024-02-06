/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:33:22 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/06 17:29:54 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_player(t_cub3d *cub3d, int x, int y) 
{
	int yy = 1;

	while(yy <= 5)
	{
		my_pixel_put(&cub3d->map_view, x , y + yy, get_argb(0, 255, 0, 0)); 
		my_pixel_put(&cub3d->map_view, x - 1 , y + yy, get_argb(0, 255, 0, 0)); 
		my_pixel_put(&cub3d->map_view, x + 1 , y + yy, get_argb(0, 255, 0, 0)); 
		if(yy >= 2 && yy <= 4)
		{
			my_pixel_put(&cub3d->map_view, x - 2, y + yy, get_argb(0, 255, 0, 0)); 
			my_pixel_put(&cub3d->map_view, x + 2, y + yy, get_argb(0, 255, 0, 0)); 
		}
		yy++;
	}
} 