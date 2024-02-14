/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:10:51 by paulo             #+#    #+#             */
/*   Updated: 2024/02/14 16:34:32 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

struct s_rotation
{
	double	radians;
	double	cos_angle;
	double	sin_angle;
	double	new_dir_x;
	double	new_dir_y;
	double	new_fov_x;
	double	new_fov_y;
}			t_rotation;

void	rotation(t_cub3d *cub3d, double angle)
{
	struct s_rotation	data;

	data.radians = angle * (MY_PI / 180.0);
	data.cos_angle = cos(data.radians);
	data.sin_angle = sin(data.radians);
	data.new_dir_x = cub3d->player.view_dir.x * data.cos_angle - cub3d->player.view_dir.y * \
	data.sin_angle;
	data.new_dir_y = cub3d->player.view_dir.x * data.sin_angle + cub3d->player.view_dir.y * \
	data.cos_angle;
	cub3d->player.view_dir.x = data.new_dir_x;
	cub3d->player.view_dir.y = data.new_dir_y;
/* 	data.new_fov_x = player->fovx * data.cos_angle - player->fovy * \
	data.sin_angle;
	data.new_fov_y = player->fovx * data.sin_angle + player->fovy * \
	data.cos_angle;
	player->fovx = data.new_fov_x;
	player->fovy = data.new_fov_y;
 */}

int	move_mouse(int x, int y, t_cub3d *cub3d)
{
	int	move_x;

	move_x = x - (SCREEN_WIDTH / 2);
	(void) y;
	rotation(cub3d, MOUSE_SENSITIVITY * move_x);
	mlx_mouse_move(cub3d->mlx, cub3d->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (1);
}

/* int	key_release(int key, t_cub3d *cub)
{
	if (key == KEY_W)
		cub->player.move.w = 0;
	if (key == KEY_S)
		cub->player.move.s = 0;
	if (key == KEY_A)
		cub->player.move.a = 0;
	if (key == KEY_D)
		cub->player.move.d = 0;
	return (0);
}

int	get_key(int key, t_cub3d *cub)
{
	if (key == KEY_ESC)
		free_exit(cub, "Exit was successfull");
	if (key == KEY_W)
		cub->player.move.w = 1;
	if (key == KEY_S)
		cub->player.move.s = 1;
	if (key == KEY_A)
		cub->player.move.a = 1;
	if (key == KEY_D)
		cub->player.move.d = 1;
	if (key == KEY_F && cub->door.x >= 0 && cub->press_f)
	{
		if (cub->door.hp)
			cub->door.hp = 0;
		else
			cub->door.hp = 1;
	}
	return (0);
}
 */