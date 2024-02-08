/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:53:47 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/08 11:06:41 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
 * Inicializa as texturas do jogo.
 * 
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 */
void	init_textures(t_cub3d *cub3d)
{
	cub3d->textures.north = 0;
	cub3d->textures.south = 0;
	cub3d->textures.east = 0;
	cub3d->textures.west = 0;
	cub3d->textures.floor = 0;
	cub3d->textures.ceiling = 0;
	cub3d->textures.north_path = NULL;
	cub3d->textures.south_path = NULL;
	cub3d->textures.west_path = NULL;
	cub3d->textures.east_path = NULL;
}

/**
 * Inicializa as variáveis.
 *
 * Esta função atribui valores iniciais às variáveis, como texturas, mapa,
 * posição do jogador, direção do jogador, etc.
 *
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 */
void	init_var(t_cub3d *cub3d)
{
	cub3d->cub = NULL;
	cub3d->map = NULL;
	cub3d->map_total_lines = 0;
	cub3d->start_map = 0;
	cub3d->map_max_column = 0;
	cub3d->mini_map_visible = false;
	cub3d->player.position.x = 0;
	cub3d->player.position.y = 0;
	cub3d->player_number = 0;
	cub3d->player_direction = '9';
	cub3d->player.move.w = 0;
	cub3d->player.move.a = 0;
	cub3d->player.move.s = 0;
	cub3d->player.move.d = 0;
	cub3d->player.move.left = 0;
	cub3d->player.move.right = 0;
	init_textures(cub3d);
	init_ray(cub3d);
}
