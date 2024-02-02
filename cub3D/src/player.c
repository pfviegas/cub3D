/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:15:56 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/02 17:16:59 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_hitbox	define_hitbox(t_position    player_position)
{
	t_hitbox	hitbox;

	hitbox.top_left_corner.x = player_position.x - 0.25;
	hitbox.top_right_corner.x = player_position.x + 0.25;
	hitbox.bottom_left_corner.x = player_position.x - 0.25;
	hitbox.bottom_right_corner.x = player_position.x + 0.25;
	hitbox.top_left_corner.y = player_position.y - 0.25;
	hitbox.top_right_corner.y = player_position.y - 0.25;
	hitbox.bottom_left_corner.y = player_position.y + 0.25;
	hitbox.bottom_right_corner.y = player_position.y + 0.25;
	return (hitbox);
}

t_player_info   create_player(t_cub3d *cub3d)
{
    cub3d->player.hitbox = define_hitbox(cub3d->player.position);
	cub3d->player.view_dir.x = cos(cub3d->player.dirx);
	cub3d->player.view_dir.y = sin(cub3d->player.dirx);
	cub3d->player.plane.x = -sin(cub3d->player.dirx);
	cub3d->player.plane.y = cos(cub3d->player.dirx);

    return (cub3d->player);
}
