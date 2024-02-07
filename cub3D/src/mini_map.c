/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:37:45 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/07 15:49:55 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_square(t_cub3d *cub3d, int x, int y, int color)
{
	int	x_end;
	int	y_end;
	int	y_reset;

	x_end = x + MINIMAP_SCALE;
	y_end = y + MINIMAP_SCALE;
	y_reset = y;
	while (x < x_end && x < SCREEN_WIDTH)
	{
		y = y_reset;
		while (y < y_end && y < SCREEN_HEIGHT)
		{
			my_pixel_put(&cub3d->map_view, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_mini_map1(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == '0')
				draw_square(cub3d, (j) * MINIMAP_SCALE, (i)
					* MINIMAP_SCALE, get_argb(0, cub3d->textures.floor_color[0], cub3d->textures.floor_color[1], cub3d->textures.floor_color[2]));
			else if (cub3d->map[i][j] == '1')
				draw_square(cub3d, (j) * MINIMAP_SCALE, (i)
					* MINIMAP_SCALE, get_argb(0, 27, 255, 30));
			else if (cub3d->map[i][j] != '\n' && cub3d->map[i][j] != ' ')
				draw_square(cub3d, (j) * MINIMAP_SCALE, (i)
					* MINIMAP_SCALE, get_argb(0, 228, 227, 225));
		}
	}
	// printf("cub3d->player.position.x = %f\n", cub3d->player.position.x);
	// printf("cub3d->player.position.y = %f\n", cub3d->player.position.y);
	
	draw_player(cub3d, (cub3d->player.position.x * MINIMAP_SCALE), (cub3d->player.position.y * MINIMAP_SCALE));
	draw_bar(cub3d, (cub3d->player.position.x) * MINIMAP_SCALE, (cub3d->player.position.y) * MINIMAP_SCALE, (-0.5));
	draw_bar(cub3d, (cub3d->player.position.x) * MINIMAP_SCALE, (cub3d->player.position.y) * MINIMAP_SCALE, (0.5));
}
	//draw_player(cub3d, (cub3d->player.position.x) * MINIMAP_SCALE,
	//	(cub3d->player.position.y) * MINIMAP_SCALE, get_argb(0, 255, 0, 0));

