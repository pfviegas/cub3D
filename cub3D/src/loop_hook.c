/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:40:40 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/07 11:17:43 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	loop_hook(t_cub3d *cub3d)
{
	static unsigned int	frames;
	t_position			old_position;

	frames++;
	if (!(frames % (10000 / REFRESH_RATE)))
	{
			render_3d_view(cub3d);
			if (cub3d->mini_map_visible == true)
				render_mini_map1(cub3d);
			mlx_put_image_to_window(cub3d->mlx, cub3d->win, 
				cub3d->map_view.img, 0, 0);
			old_position = cub3d->player.position;
			
			//check_colision(cub3d, cub3d->player.hitbox, old_position);
			
			if (check_colision(cub3d, cub3d->player.hitbox))
			{
				//printf("colisao");
				// cub3d->player.position = find_new_position(cub3d->player.position,
				// 		old_position, cub3d->map);
				// cub3d->player.hitbox = define_player_hitbox(
				// 		cub3d->player.position);
			}

	}
	return (0);
}

bool	check_colision(t_cub3d *cub3d, t_hitbox hitbox)
 {
		if (cub3d->map[(int)hitbox.bottom_left_corner.y][(int)hitbox.bottom_left_corner.x] == '1')
		return (true);
	if (cub3d->map[(int)hitbox.bottom_right_corner.y][(int)hitbox.bottom_right_corner.x] == '1')
		return (true);
	if (cub3d->map[(int)hitbox.top_left_corner.y][(int)hitbox.top_left_corner.x] == '1')
		return (true);
	if (cub3d->map[(int)hitbox.top_right_corner.y][(int)hitbox.top_right_corner.x] == '1')
		return (true);
	return (false);
	
// 	int flag;
	
// 	flag = 0;
// 	if (cub3d->map[(int)hitbox.bottom_left_corner.y][(int)hitbox.bottom_left_corner.x] == '1')
// 		flag = 1;
// 	if (cub3d->map[(int)hitbox.bottom_right_corner.y][(int)hitbox.bottom_right_corner.x] == '1')
// 		flag = 1;
// 	if (cub3d->map[(int)hitbox.top_left_corner.y][(int)hitbox.top_left_corner.x] == '1')
// 		flag = 1;
// 	if (cub3d->map[(int)hitbox.top_right_corner.y][(int)hitbox.top_right_corner.x] == '1')
// 		flag = 1;
// 	if(flag == 1)
// 	{
// 		cub3d->player.position = find_new_position(cub3d->player.position, old_position, cub3d->map);
// 		cub3d->player.hitbox = define_player_hitbox(cub3d->player.position);
// 	}
	
// 	return (false);
}

// t_position	find_new_position(t_position wanted_position,
// 		t_position old_position, t_map_info map)
// {
// 	t_position	new_position;

// 	new_position.x = wanted_position.x;
// 	new_position.y = old_position.y;
// 	if (!check_colision(define_player_hitbox(new_position), map))
// 		return (new_position);
// 	new_position.x = old_position.x;
// 	new_position.y = wanted_position.y;
// 	if (!check_colision(define_player_hitbox(new_position), map))
// 		return (new_position);
// 	new_position.x = old_position.x;
// 	new_position.y = old_position.y;
// 	return (new_position);
// }
