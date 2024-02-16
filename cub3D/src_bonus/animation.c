/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: correia <correia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:44:09 by correia           #+#    #+#             */
/*   Updated: 2024/02/16 11:04:15 by correia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"
void	check_textures_sprites(t_cub3d *cub3d)
{
	int fd;
	
	cub3d->textures.enemy_path = "./images/sprites/enemy1.xpm";
	fd = open(cub3d->textures.enemy_path, O_RDONLY);
	if (fd == -1)
		quit("Error:\n Enemy image missing.", cub3d, 99);
	close(fd);
}

void	enemy_validation(t_cub3d *cub3d, int line, int col)
{
	cub3d->textures.enemy++;
	cub3d->map[line][col] = 'Z';
	if (cub3d->textures.enemy > 1)
		quit("Error:\n Only one enemy allowed.", cub3d, 99);
}

void	load_sprite(t_cub3d *cub3d, t_image_data *enemy, char *path)
{
	int	tex_w;
	int	tex_h;

	tex_w = ENEMY_WIDTH;
	tex_h = ENEMY_HEIGHT;
	enemy->img = mlx_xpm_file_to_image(cub3d->mlx, path, &tex_w, &tex_h);
	enemy->addr = mlx_get_data_addr(enemy->img,
			&enemy->bits_per_pixel,
			&enemy->line_length, 
			&enemy->endian);
	//nemy->animation.frame = 0;
	//enemy->animation.max = 9;
	//enemy->animation.size = 80;
}

void	init_sprite(t_cub3d *cub3d)
{
	int	y;
	int	x;

	y = -1;
//	cub3d->enemy.hp = 0;
	//cub3d->enemy.x = -1.0;
	//cub3d->enemy.y = -1.0;
	while (cub3d->map[++y])
	{
		x = -1;
		while (cub3d->map[y][++x])
		{
			if (cub3d->map[y][x] == 'Z')
			{
                mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->enemy.img, x * TEXTURE_HEIGHT, y * TEXTURE_WIDTH);
				//cub3d->enemy.x = (float)(x + 0.5);
				//cub3d->enemy.y = (float)(y + 0.5);
				//cub3d->enemy.hp = 1;
			}
		}
	}
}

void	read_frame(t_cub3d *cub3d)
{
	if (cub3d->enemy.frame > 5)
		cub3d->enemy.frame = 1;
	if (cub3d->enemy.img)
		mlx_destroy_image(cub3d->mlx, cub3d->enemy.img);
	if (cub3d->enemy.frame == 1)
		load_sprite(cub3d, &cub3d->enemy, "./images/sprites/enemy1.xpm");
	else if (cub3d->enemy.frame == 2)
		load_sprite(cub3d, &cub3d->enemy, "./images/sprites/enemy2.xpm");
	else if (cub3d->enemy.frame == 3)
		load_sprite(cub3d, &cub3d->enemy, "./images/sprites/enemy3.xpm");
	else if (cub3d->enemy.frame == 4)
		load_sprite(cub3d, &cub3d->enemy, "./images/sprites/enemy4.xpm");
	else if (cub3d->enemy.frame == 5)
		load_sprite(cub3d, &cub3d->enemy, "./images/sprites/enemy5.xpm");
	//usleep(100000);
	cub3d->enemy.frame++;
}

/*
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
*/


