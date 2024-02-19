/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:10:51 by paulo             #+#    #+#             */
/*   Updated: 2024/02/19 14:50:37 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Atualiza a visão do jogador de acordo com o movimento do rato.
 *
 * @param x     coordenada x da posicao do rato.
 * @param y     coordenada x da posicao do rato.
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @return      Retorna sempre 0.
 */
int	move_mouse(int x, int y, t_cub3d *cub3d)
{
	int	move_x;

	(void) y;
	move_x = x - (SCREEN_WIDTH / 2);
	if (move_x < 0)
		look_left_mouse(cub3d);
	else if (move_x > 0)
		look_right_mouse(cub3d);
	mlx_mouse_move(cub3d->mlx, cub3d->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}

void	look_left_mouse(t_cub3d *cub3d)
{
	cub3d->player.dirx -= MOVE_SPEED * 0.006;
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
void	look_right_mouse(t_cub3d *cub3d)
{
	cub3d->player.dirx += MOVE_SPEED * 0.006;
	if (cub3d->player.dirx >= 2 * MY_PI)
		cub3d->player.dirx -= 2 * MY_PI;
	else if (cub3d->player.dirx <= 0)
		cub3d->player.dirx += 2 * MY_PI;
	update_look(cub3d);
}
