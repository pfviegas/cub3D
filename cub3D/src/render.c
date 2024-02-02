/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:37:40 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/02 17:30:31 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	render_3d_view(t_cub3d *cub3d)
{
	float	camera_x;
	int		pixel_w;

	camera_x = 0;
	pixel_w = -1;

	while (++pixel_w < SCREEN_WIDTH)
	{
		camera_x = 2 * pixel_w / (float)(SCREEN_WIDTH) - 1;
		cub3d->ray.ray_dir.x = cub3d->player.view_dir.x + cub3d->player.plane.x
			* camera_x;
		cub3d->ray.ray_dir.y = cub3d->player.view_dir.y + cub3d->player.plane.y
			* camera_x;
		// cub3d->player.map_posx = (int)cub3d->player.position.x;
		// cub3d->player.map_posy = (int)cub3d->player.position.y;
		cub3d->ray.delta.x = sqrt(1 + pow(cub3d->ray.ray_dir.y, 2) / pow(cub3d->ray.ray_dir.x, 2));
		cub3d->ray.delta.y = sqrt(1 + pow(cub3d->ray.ray_dir.x, 2) / pow(cub3d->ray.ray_dir.y, 2));
		calc_step_and_side(cub3d);
		// find_wall(cub3d);
		// calc_wall_height(cub3d);
		// draw_scene(cub3d, pixel_w);
	}
}

void	calc_step_and_side(t_cub3d *cub3d)
{
	if (cub3d->ray.ray_dir.x < 0)
	{
		cub3d->ray.step.x = -1;
		cub3d->ray.side_dist.x = (cub3d->player.position.x
				- (int)cub3d->player.position.x) * cub3d->ray.delta.x;
	}
	else
	{
		cub3d->ray.step.x = 1;
		cub3d->ray.side_dist.x = ((int)cub3d->player.position.x + 1
				- cub3d->player.position.x) * cub3d->ray.delta.x;
	}
	if (cub3d->ray.ray_dir.y < 0)
	{
		cub3d->ray.step.y = -1;
		cub3d->ray.side_dist.y = (cub3d->player.position.y
				- (int)cub3d->player.position.y) * cub3d->ray.delta.y;
	}
	else
	{
		cub3d->ray.step.y = 1;
		cub3d->ray.side_dist.y = ((int)cub3d->player.position.y + 1
				- cub3d->player.position.y) * cub3d->ray.delta.y;
	}
}