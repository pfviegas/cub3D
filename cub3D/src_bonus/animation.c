/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: correia <correia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:44:09 by correia           #+#    #+#             */
/*   Updated: 2024/02/15 11:58:58 by correia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	check_textures_sprites(t_cub3d *cub3d)
{
	int fd;
	
	cub3d->textures.enemy_path = "../images/sprites/enemy.xpm";
	fd = open(cub3d->textures.north_path, O_RDONLY);
	if (fd == -1)
		quit("Error:\n Enemy image missing.", cub3d, 99);
	close(fd);
}
void	enemy_validation(t_cub3d *cub3d, int line, int col)
{
	cub3d->textures.enemy++;
    cub3d->map[line][col] = '0';
	if (cub3d->textures.east > 1)
		quit("Error:\n ", cub3d, 99);
}

void	load_sprite(t_cub3d *cub3d, t_object *enemy, char *path)
{
	int	tex_w;
	int	tex_h;

	tex_w = TEXTURE_ENEMY_WIDTH;
	tex_h = TEXTURE_ENEMY_HEIGHT;
	enemy->animation.img.img = mlx_xpm_file_to_image(cub3d->mlx, path, &tex_w, &tex_h);
	enemy->animation.img.addr = mlx_get_data_addr(enemy->animation.img.img,
			&enemy->animation.img.bits_per_pixel,
			&enemy->animation.img.line_length, 
			&enemy->animation.img.endian);
	enemy->animation.frame = 0;
	enemy->animation.max = 9;
	enemy->animation.size = 80;
}
int	init_sprite(t_cub3d *cub3d)
{
	int	y;
	int	x;

	y = -1;
	cub3d->enemy.hp = 0;
	while (cub3d->map[++y])
	{
		x = -1;
		while (cub3d->map[y][++x])
		{
			if (cub3d->map[y][x] == 'Z')
			{
				cub3d->enemy.x = (double)(x + 0.5);
				cub3d->enemy.y = (double)(y + 0.5);
				cub3d->enemy.hp = 1;
				return (1);
			}
		}
	}
	cub3d->enemy.x = -1.0;
	return (0);
}

void	do_enemy_thing(t_cub3d *cub3d, int *i)
{
	gettimeofday(&cub3d->enemy.animation.old_time, NULL);
	cub3d->enemy.animation.frame += *i;
	if (cub3d->enemy.animation.frame > 9 || 
		cub3d->enemy.animation.frame < 0)
	{
		*i *= -1;
		cub3d->enemy.animation.frame += *i;
	}
}

int	update_enemy_animation(t_cub3d *cub3d)
{
	static int		i;
	static double	fps;
	double			time;

	if (!cub3d->enemy.hp || cub3d->enemy.x < 0)
		return (0);
	if (!i)
		i = 1;
	if (!fps)
		gettimeofday(&cub3d->enemy.animation.old_time, NULL);
	fps = 1.0 / (cub3d->enemy.animation.max / 1.7);
	gettimeofday(&cub3d->enemy.animation.new_time, NULL);
	time = (cub3d->enemy.animation.new_time.tv_sec - 
			cub3d->enemy.animation.old_time.tv_sec);
	time += (double)(cub3d->enemy.animation.new_time.tv_usec - 
			cub3d->enemy.animation.old_time.tv_usec) / 1000000;
	if (time > fps)
		do_enemy_thing(cub3d, &i);
	return (0);
}