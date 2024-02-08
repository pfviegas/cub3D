/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:40:40 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/08 10:27:40 by pveiga-c         ###   ########.fr       */
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
			update_possition_player(cub3d);
			//check_colision(cub3d, cub3d->player.hitbox, old_position);
			if (check_colision(cub3d, cub3d->player.hitbox))
			{
				// printf("colisao\n");
				cub3d->player.position = find_new_position(cub3d->player.position, old_position, cub3d);
				cub3d->player.hitbox = define_hitbox(cub3d->player.position);
			}
			//key_handling and key_realized
	}
	return (0);
}

bool	check_colision(t_cub3d *cub3d, t_hitbox hitbox)
 {
	printf("cub3d->player.position.x = %f\n", cub3d->player.position.x);
	printf("hitbox.bottom_left_corner.x: %f\n", hitbox.bottom_left_corner.x);
	printf("hitbox.bottom_left_corner.x -> int: %d\n", (int)hitbox.bottom_left_corner.x);
	printf("cub3d->player.position.y = %f\n", cub3d->player.position.y);
	printf("hitbox.bottom_left_corner.y: %f\n", hitbox.bottom_left_corner.y);
	printf("hitbox.bottom_left_corner.y -> int: %d\n", (int)hitbox.bottom_left_corner.y);
	
	printf("current map[%d][%d]: %c\n", (int)hitbox.bottom_left_corner.y, (int)hitbox.bottom_left_corner.x, cub3d->map[(int)hitbox.bottom_left_corner.y][(int)hitbox.bottom_left_corner.x]);
	printf("map[%d][%d]: %c\n",(int)cub3d->player.position.y, (int)cub3d->player.position.x,cub3d->map[(int)cub3d->player.position.y][(int)cub3d->player.position.x]);
	printf("map: %c\n", cub3d->map[11][3]);
	if (cub3d->map[(int)hitbox.bottom_left_corner.y][(int)hitbox.bottom_left_corner.x] == '1')
		{
			printf("colisao\n");			
			return (true);
		}
	if (cub3d->map[(int)hitbox.bottom_right_corner.y][(int)hitbox.bottom_right_corner.x] == '1')
		{
			printf("colisao\n");			
			return (true);
		}
	if (cub3d->map[(int)hitbox.top_left_corner.y][(int)hitbox.top_left_corner.x] == '1')
		{
			printf("colisao\n");			
			return (true);
		}
	if (cub3d->map[(int)hitbox.top_right_corner.y][(int)hitbox.top_right_corner.x] == '1')
		{
			printf("colisao\n");			
			return (true);
		}
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

t_position	find_new_position(t_position wanted_position, t_position old_position, t_cub3d *cub3d)
{
	t_position	new_position;

	new_position.x = wanted_position.x;
	new_position.y = old_position.y;
	if (!check_colision(cub3d, define_hitbox(new_position)))
		return (new_position);
	new_position.x = old_position.x;
	new_position.y = wanted_position.y;
	if (!check_colision(cub3d, define_hitbox(new_position)))
		return (new_position);
	new_position.x = old_position.x;
	new_position.y = old_position.y;
	return (new_position);
}
