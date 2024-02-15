/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:35:46 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/15 17:10:05 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/**
 * Move o jogador para frente.
 * Atualiza a posição do jogador de acordo com a velocidade de movimento 
 * e a direção atual.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	move_front(t_cub3d *cub3d)
{
	cub3d->player.position.x += MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
	cub3d->player.position.y += MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
}

/**
 * Move o jogador para trás.
 * Atualiza a posição do jogador de acordo com a velocidade de movimento 
 * e a direção atual.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	move_back(t_cub3d *cub3d)
{
	cub3d->player.position.x -= MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
	cub3d->player.position.y -= MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
}

/**
 * Move o jogador para a direita.
 * Atualiza a posição do jogador de acordo com a velocidade de movimento 
 * e a direção atual.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	move_right(t_cub3d *cub3d)
{
	cub3d->player.position.x -= MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
	cub3d->player.position.y += MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
}

/**
 * Move o jogador para a esquerda.
 * Atualiza a posição do jogador de acordo com a velocidade de movimento 
 * e a direção atual.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	move_left(t_cub3d *cub3d)
{
	cub3d->player.position.x += MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
	cub3d->player.position.y -= MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
}

/**
 * Atualiza a posição do jogador.
 * Atualiza a posição do jogador de acordo com as teclas pressionadas.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	update_position_player(t_cub3d *cub3d)
{
	if (cub3d->player.move.a == 1)
		move_left(cub3d);
	if (cub3d->player.move.w == 1)
		move_front(cub3d);
	if (cub3d->player.move.s == 1)
		move_back(cub3d);
	if (cub3d->player.move.d == 1)
		move_right(cub3d);
	if (cub3d->player.move.left == 1)
		look_left(cub3d);
	if (cub3d->player.move.right == 1)
		look_right(cub3d);
	cub3d->player.hitbox = define_hitbox(cub3d->player.position);
}
