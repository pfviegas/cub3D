/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:53:47 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/06 16:15:59 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Inicializa as imagens utilizadas.
 * 
 * @param cub3d Ponteiro para a estrutura que contém os dados.
 */
void	init_images(t_cub3d *cub3d)
{
	int len;

	len = IMAGE_WIDTH;
	cub3d->img.wall = mlx_xpm_file_to_image(cub3d->mlx, WALL, &len, &len);
	cub3d->img.floor = mlx_xpm_file_to_image(cub3d->mlx, FLOOR, &len, &len);
}

/**
 * Inicializa a estrutura de dados 'ray' com valores padrão.
 *
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 */
void	init_ray(t_cub3d *cub3d)
{
	cub3d->ray.delta.x = 0;
	cub3d->ray.delta.y = 0;
	cub3d->ray.ray_dir.x = 0;
	cub3d->ray.ray_dir.y = 0;
	cub3d->ray.side_dist.x = 0;
	cub3d->ray.side_dist.y = 0;
	cub3d->ray.step.x = 0;
	cub3d->ray.step.y = 0;
	cub3d->ray.wall_side = 0;
	cub3d->ray.perp_wall_dist = 0;
	cub3d->draw.start = 0;
	cub3d->draw.end = 0;
}

/**
 * Inicializa as variáveis.
 *
 * Esta função atribui valores iniciais às variáveis, como texturas, mapa,
 * posição do jogador, direção do jogador, etc.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d que contém as variáveis.
 */
void	init_var(t_cub3d *cub3d)
{
	cub3d->textures.north = 0;
	cub3d->textures.south = 0;
	cub3d->textures.east = 0;
	cub3d->textures.west = 0;
	cub3d->textures.floor = 0;
	cub3d->textures.ceiling = 0;
	cub3d->map_total_lines = 0;
	cub3d->start_map = 0;
	cub3d->cub = NULL;
	cub3d->map = NULL;
	cub3d->map_max_column = 0;
	cub3d->textures.north_path = NULL;
	cub3d->textures.south_path = NULL;
	cub3d->textures.west_path = NULL;
	cub3d->textures.east_path = NULL;
	cub3d->player.position.x = 0;
	cub3d->player.position.y = 0;
	cub3d->player_number = 0;
	cub3d->player_direction = '9';
	cub3d->mini_map_visible = false;

	cub3d->end_cub3d = 0;
	cub3d->move = 1;

	init_ray(cub3d);
}