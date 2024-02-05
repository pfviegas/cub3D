/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:37:40 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/05 12:00:30 by pviegas          ###   ########.fr       */
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
		cub3d->player.map_x = (int)cub3d->player.position.x;
		cub3d->player.map_y = (int)cub3d->player.position.y;
		cub3d->ray.delta.x = sqrt(1 + pow(cub3d->ray.ray_dir.y, 2) / pow(cub3d->ray.ray_dir.x, 2));
		cub3d->ray.delta.y = sqrt(1 + pow(cub3d->ray.ray_dir.x, 2) / pow(cub3d->ray.ray_dir.y, 2));
		calc_step_and_side(cub3d);
		find_wall(cub3d);
		calc_wall_height(cub3d);
		draw_scene(cub3d, pixel_w);
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

void	find_wall(t_cub3d *cub3d)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub3d->ray.side_dist.x < cub3d->ray.side_dist.y)
		{
			cub3d->ray.side_dist.x += cub3d->ray.delta.x;
			cub3d->player.map_x += cub3d->ray.step.x;
			cub3d->ray.wall_side = 0;
		}
		else
		{
			cub3d->ray.side_dist.y += cub3d->ray.delta.y;
			cub3d->player.map_y += cub3d->ray.step.y;
			cub3d->ray.wall_side = 1;
		}
		if (cub3d->map[cub3d->player.map_y][cub3d->player.map_x] == '1')
			hit = 1;
	}
}

void	calc_wall_height(t_cub3d *cub3d)
{
	cub3d->tex.wall_line_h = 0;
	if (cub3d->ray.wall_side == 0)
		cub3d->ray.prep_wall_dist = fabs((cub3d->player.map_x
					- cub3d->player.position.x + (1 - cub3d->ray.step.x) / 2)
				/ cub3d->ray.ray_dir.x);
	else
		cub3d->ray.prep_wall_dist = fabs((cub3d->player.map_y
					- cub3d->player.position.y + (1 - cub3d->ray.step.y) / 2)
				/ cub3d->ray.ray_dir.y);
	cub3d->tex.wall_line_h = (int)(SCREEN_WIDTH / cub3d->ray.prep_wall_dist);
	cub3d->draw.start = -cub3d->tex.wall_line_h / 2 + SCREEN_HEIGHT / 2;
	if (cub3d->draw.start < 0)
		cub3d->draw.start = 0;
	cub3d->draw.end = cub3d->tex.wall_line_h / 2 + SCREEN_HEIGHT / 2;
	if (cub3d->draw.end >= SCREEN_HEIGHT)
		cub3d->draw.end = SCREEN_HEIGHT - 1;
}

void	draw_scene(t_cub3d *cub3d, int pixel_w)
{
	int	pixel_h;

	pixel_h = -1;
	get_tex_data(cub3d);
	while (++pixel_h < SCREEN_HEIGHT)
	{
		printf("cub3d->draw.start: %d\n", cub3d->draw.start);
		if (pixel_h < cub3d->draw.start)
			// my_pixel_put(&cub3d->scene, pixel_w, pixel_h,
			// 	cub3d->map.ceiling_color);
			my_pixel_put(&cub3d->map_view, pixel_w, pixel_h,
			 	create_trgb(0, cub3d->textures.ceiling_color[0], cub3d->textures.ceiling_color[1], cub3d->textures.ceiling_color[2]));
		else if (pixel_h > cub3d->draw.end)
			// my_pixel_put(&cub3d->scene, pixel_w, pixel_h,
			// 	cub3d->map.floor_color);
			 my_pixel_put(&cub3d->map_view, pixel_w, pixel_h,
			 	create_trgb(0, cub3d->textures.floor_color[0], cub3d->textures.floor_color[1], cub3d->textures.floor_color[2]));
		else
			draw_wall(cub3d, pixel_w, pixel_h);
	}
}

void	get_tex_data(t_cub3d *cub3d)
{
	float	wall_x;

	cub3d->tex.tex_x = 0;
	cub3d->tex.tex_y = 0;
	if (cub3d->ray.wall_side == 0)
		wall_x = cub3d->player.position.y + cub3d->ray.prep_wall_dist
			* cub3d->ray.ray_dir.y;
	else
		wall_x = cub3d->player.position.x + cub3d->ray.prep_wall_dist
			* cub3d->ray.ray_dir.x;
	wall_x -= floor(wall_x);
	cub3d->tex.tex_x = (int)(wall_x * (float)TEXTURE_WIDTH);
	cub3d->tex.step = (float)TEXTURE_HEIGHT / cub3d->tex.wall_line_h;
}

void	my_pixel_put(t_image_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall(t_cub3d *cub3d, int pixel_w, int pixel_h)
{
	cub3d->tex.tex_y = (int)(((float)pixel_h - (float)SCREEN_HEIGHT / 2.0
				+ (float)cub3d->tex.wall_line_h / 2.0) * cub3d->tex.step);
	if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x > 0)
		cub3d->tex.color = get_color(&cub3d->north_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	else if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x < 0)
		cub3d->tex.color = get_color(&cub3d->south_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	else if (cub3d->ray.wall_side == 1 && cub3d->ray.ray_dir.y > 0)
		cub3d->tex.color = get_color(&cub3d->west_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	else
		cub3d->tex.color = get_color(&cub3d->east_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
				
	// printf("color: %d\n", cub3d->tex.color);
	// printf("pixel_w: %d\n", pixel_w);
	// printf("pixel_h: %d\n", pixel_h);
	// printf("cub3d->scene: %p\n", &cub3d->map_view);

	my_pixel_put(&cub3d->map_view, pixel_w, pixel_h, cub3d->tex.color);
}

unsigned int	get_color(t_image_data *img, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
