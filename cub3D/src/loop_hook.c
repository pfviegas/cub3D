/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:40:40 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/05 12:05:55 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	loop_hook(t_cub3d *cub3d)
{
	static unsigned int	frames;
//	t_position			old_position;

	frames++;
	if (!(frames % (10000 / REFRESH_RATE)))
	{
			render_3d_view(cub3d);
			if (cub3d->mini_map_visible == true)
				render_mini_map(cub3d);
			mlx_put_image_to_window(cub3d->mlx, cub3d->win, 
				cub3d->map_view.img, 0, 0);
/*
			old_position = cub3d->player.position;
			update_position(cub3d);
			if (check_colision(cub3d->player.hitbox, cub3d->map))
			{
				cub3d->player.position = find_new_position(cub3d->player.position,
						old_position, cub3d->map);
				cub3d->player.hitbox = define_player_hitbox(
						cub3d->player.position);
			}
*/
	}
	return (0);
}
