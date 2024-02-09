/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: correia <correia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:37:40 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/09 11:04:45 by correia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Renderiza a visão 3D do jogo.
 *
 * @param cub3d Ponteiro para a estrutura que contém os dados.
 * 
 * camera_x = posição x da câmera na tela.
 * -1 lado esquerdo da tela
 * 0 centro da tela
 * 1 lado direito da tela
 * 
 * ray_dir.x = direção x do raio
 * ray.delta.x = distância entre os raios
 * player.view_dir.x = direção x da visão do jogador
 * player.plane.x = direção x do plano da câmera
 * player.map_x = coordenada x do mapa
 */
void render_3d_view(t_cub3d *cub3d)
{
	float camera_x;
	int pixel_w;

	pixel_w = -1;
	while (++pixel_w < SCREEN_WIDTH)
	{
		camera_x = 2 * pixel_w / (float)(SCREEN_WIDTH) - 1;
		cub3d->ray.ray_dir.x = cub3d->player.view_dir.x + cub3d->player.plane.x * camera_x;
		cub3d->ray.ray_dir.y = cub3d->player.view_dir.y + cub3d->player.plane.y * camera_x;
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

/**
 * Função responsável por calcular os passos e as distâncias laterais do raio.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * 
 * cub3d->ray.step.x = passo a dar pelo player 
 * 						(-1 move-se para a esquerda do eixo x)
 *						(1 move-se para a direita do eixo x)
 * cub3d->ray.step.y = passoint				key_press(int keycode, t_cub3d *cub3d);
int				key_release(int keycode, t_cub3d *cub3d); a dar pelo player 
 * 						(-1 move-se para a esquerda do eixo y)
 *						(1 move-se para a direita do eixo y)
 * ray.side_dist.x = distância lateral x
 * ray.side_dist.y = distância lateral y
 */
void calc_step_and_side(t_cub3d *cub3d)
{
	if (cub3d->ray.ray_dir.x < 0)
	{
		cub3d->ray.step.x = -1;
		cub3d->ray.side_dist.x = (cub3d->player.position.x - (int)cub3d->player.position.x) * cub3d->ray.delta.x;
	}
	else
	{
		cub3d->ray.step.x = 1;
		cub3d->ray.side_dist.x = ((int)cub3d->player.position.x + 1 - cub3d->player.position.x) * cub3d->ray.delta.x;
	}
	if (cub3d->ray.ray_dir.y < 0)
	{
		cub3d->ray.step.y = -1;
		cub3d->ray.side_dist.y = (cub3d->player.position.y - (int)cub3d->player.position.y) * cub3d->ray.delta.y;
	}
	else
	{
		cub3d->ray.step.y = 1;
		cub3d->ray.side_dist.y = ((int)cub3d->player.position.y + 1 - cub3d->player.position.y) * cub3d->ray.delta.y;
	}
}

/**
 * Função responsável por encontrar a parede em que o raio colide.
 * DDA Algorithm
 * 
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * wall_side = 0 -> horizontal (x)
 * wall_side = 1 -> vertical (y)
 */
void find_wall(t_cub3d *cub3d)
{
	int hit;

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

/**
 * Calcula a altura da parede.
 * 
 * Calcula a altura da parede com base na distância preparada
 * e define os valores de início e fim para desenhar a parede na tela.
 * 
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 */
void	calc_wall_height(t_cub3d *cub3d)
{
	cub3d->tex.wall_line_h = 0;
	if (cub3d->ray.wall_side == 0)
		cub3d->ray.perp_wall_dist = fabs((cub3d->player.map_x
					- cub3d->player.position.x + (1 - cub3d->ray.step.x) / 2)
				/ cub3d->ray.ray_dir.x);
	else
		cub3d->ray.perp_wall_dist = fabs((cub3d->player.map_y
					- cub3d->player.position.y + (1 - cub3d->ray.step.y) / 2)
				/ cub3d->ray.ray_dir.y);
	cub3d->tex.wall_line_h = (int)(SCREEN_HEIGHT / cub3d->ray.perp_wall_dist);
	cub3d->draw.start = -cub3d->tex.wall_line_h / 2 + SCREEN_HEIGHT / 2;
	if (cub3d->draw.start < 0)
		cub3d->draw.start = 0;
	cub3d->draw.end = cub3d->tex.wall_line_h / 2 + SCREEN_HEIGHT / 2;
	if (cub3d->draw.end >= SCREEN_HEIGHT)
		cub3d->draw.end = SCREEN_HEIGHT - 1;
}
