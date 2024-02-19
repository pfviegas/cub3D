/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:10:51 by paulo             #+#    #+#             */
/*   Updated: 2024/02/19 14:43:07 by pveiga-c         ###   ########.fr       */
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
		look_left(cub3d);
	else if (move_x > 0)
		look_right(cub3d);
	mlx_mouse_move(cub3d->mlx, cub3d->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}
