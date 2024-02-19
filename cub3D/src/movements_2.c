/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:35:46 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/19 14:41:28 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Atualiza a direção de visualização do jogador e a direção dos raios.
 * 
 * Atualiza as coordenadas x e y da direção de visualização do jogador com base 
 * no ângulo de direção atual. Além disso, atualiza as coordenadas x e y da 
 * direção dos raios para que sejam iguais à direção de visualização do jogador.
 * Também atualiza as coordenadas x e y do plano de projeção perpendicular 
 * à direção de visualização do jogador.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	update_look(t_cub3d *cub3d)
{
	cub3d->player.view_dir.x = cos(cub3d->player.dirx);
	cub3d->player.view_dir.y = sin(cub3d->player.dirx);
	cub3d->ray.ray_dir.x = cos(cub3d->player.dirx);
	cub3d->ray.ray_dir.y = sin(cub3d->player.dirx);
	cub3d->player.plane.x = -sin(cub3d->player.dirx);
	cub3d->player.plane.y = cos(cub3d->player.dirx);
}

/**
 * Roda o jogador para a esquerda.
 * Atualiza a posição do jogador de acordo com a velocidade de movimento 
 * e a direção atual.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	look_left(t_cub3d *cub3d)
{
	cub3d->player.dirx -= MOVE_SPEED * 0.01;
	if (cub3d->player.dirx >= 2 * MY_PI)
		cub3d->player.dirx -= 2 * MY_PI;
	else if (cub3d->player.dirx <= 0)
		cub3d->player.dirx += 2 * MY_PI;
	update_look(cub3d);
}

/**
 * Roda o jogador para a direita.
 * Atualiza a posição do jogador de acordo com a velocidade de movimento 
 * e a direção atual.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	look_right(t_cub3d *cub3d)
{
	cub3d->player.dirx += MOVE_SPEED * 0.01;
	if (cub3d->player.dirx >= 2 * MY_PI)
		cub3d->player.dirx -= 2 * MY_PI;
	else if (cub3d->player.dirx <= 0)
		cub3d->player.dirx += 2 * MY_PI;
	update_look(cub3d);
}

/**
 * Verifica que tecla foi pressionada e muda-lhe o estado.
  *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
int	key_press(int keycode, t_cub3d *cub3d)
{
	if (keycode == A)
		cub3d->player.move.a = 1;
	if (keycode == W)
		cub3d->player.move.w = 1;
	if (keycode == S)
		cub3d->player.move.s = 1;
	if (keycode == D)
		cub3d->player.move.d = 1;
	if (keycode == ARROW_LEFT)
		cub3d->player.move.left = 1;
	if (keycode == ARROW_RIGHT)
		cub3d->player.move.right = 1;
	if (keycode == ESC)
		exit_cub3d(cub3d);
	if (keycode == M)
		cub3d->mini_map_visible = !cub3d->mini_map_visible;
	return (0);
}

/**
 * Verifica que tecla foi solta e muda-lhe o estado.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
int	key_release(int keycode, t_cub3d *cub3d)
{
	if (keycode == A)
		cub3d->player.move.a = 0;
	if (keycode == W)
		cub3d->player.move.w = 0;
	if (keycode == S)
		cub3d->player.move.s = 0;
	if (keycode == D)
		cub3d->player.move.d = 0;
	if (keycode == ARROW_LEFT)
		cub3d->player.move.left = 0;
	if (keycode == ARROW_RIGHT)
		cub3d->player.move.right = 0;
	return (0);
}
