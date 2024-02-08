/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:15:56 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/08 11:47:44 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Função que define a hitbox do jogador com base na posição atual.
 *
 * @param player_position A posição atual do jogador.
 * @return A hitbox do jogador.
 */
t_hitbox define_hitbox(t_position player_position)
{
	t_hitbox hitbox;

	hitbox.top_left_corner.x = player_position.x - 0.25;
	hitbox.top_right_corner.x = player_position.x + 0.25;
	hitbox.bottom_left_corner.x = player_position.x - 0.25;
	hitbox.bottom_right_corner.x = player_position.x + 0.25;
	hitbox.top_left_corner.y = player_position.y - 0.25;
	hitbox.top_right_corner.y = player_position.y - 0.25;
	hitbox.bottom_left_corner.y = player_position.y + 0.25;
	hitbox.bottom_right_corner.y = player_position.y + 0.25;
	return (hitbox);
}

/**
 * Cria um objeto do tipo t_player_info com base nas informações do jogo cub3D.
 *
 * @param cub3d Ponteiro para a estrutura que contem as informações do jogo.
 * @return O objeto t_player_info criado.
 */
t_player_info create_player(t_cub3d *cub3d)
{
	cub3d->player.hitbox = define_hitbox(cub3d->player.position);
	cub3d->player.view_dir.x = cos(cub3d->player.dirx);
	cub3d->player.view_dir.y = sin(cub3d->player.dirx);
	cub3d->player.plane.x = -sin(cub3d->player.dirx);
	cub3d->player.plane.y = cos(cub3d->player.dirx);
	return (cub3d->player);
}
