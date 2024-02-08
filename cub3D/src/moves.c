/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:35:46 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/08 10:41:18 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	update_look(t_cub3d *cub3d)
{
	cub3d->player.view_dir.x = cos(cub3d->player.dirx);
	cub3d->player.view_dir.y = sin(cub3d->player.dirx);
	cub3d->ray.ray_dir.x = cos(cub3d->player.dirx);
	cub3d->ray.ray_dir.y = sin(cub3d->player.dirx);
	cub3d->player.plane.x = -sin(cub3d->player.dirx);
	cub3d->player.plane.y = cos(cub3d->player.dirx);	
}
// calcula a proxima coordenada quando a tecla para cima foi pressionada
void	move_front(t_cub3d *cub3d)
{
	cub3d->player.position.x += MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
	cub3d->player.position.y += MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
}

// // calcula a proxima coordenada quando a tecla para baixo foi pressionada
void	move_back(t_cub3d *cub3d)
{
	cub3d->player.position.x -= MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
	cub3d->player.position.y -= MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
}

// // calcula a proxima coordenada quando a tecla para a direita foi pressionada
void	move_right(t_cub3d *cub3d)
{
	cub3d->player.position.x -= MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
	cub3d->player.position.y += MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
}

// // calcula a proxima coordenada quando a tecla para a esquerda foi pressionada
void	move_left(t_cub3d *cub3d)
{
	cub3d->player.position.x += MOVE_SPEED * 0.01 * sin(cub3d->player.dirx);
	cub3d->player.position.y -= MOVE_SPEED * 0.01 * cos(cub3d->player.dirx);
}

void look_left(t_cub3d *cub3d)
{
	cub3d->player.dirx -= MOVE_SPEED * 0.01;
	if (cub3d->player.dirx >= 2 * MY_PI)
		cub3d->player.dirx -= 2 * MY_PI;
	else if (cub3d->player.dirx <= 0)
		cub3d->player.dirx += 2 * MY_PI;
	update_look(cub3d);
}

void look_right(t_cub3d *cub3d)
{
	cub3d->player.dirx += MOVE_SPEED * 0.01;
	if (cub3d->player.dirx >= 2 * MY_PI)
		cub3d->player.dirx -= 2 * MY_PI;
	else if (cub3d->player.dirx <= 0)
		cub3d->player.dirx += 2 * MY_PI;
	update_look(cub3d);
}

// trata os movimentos do jogador
void	update_possition_player(t_cub3d *cub3d)
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
