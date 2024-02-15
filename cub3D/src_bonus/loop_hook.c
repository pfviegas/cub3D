/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:40:40 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/15 15:00:12 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/**
 * Executa o loop principal do jogo.
 * Atualiza a renderização da visão 3D, do mini mapa e da posição do jogador.
 * Verifica colisões e atualiza a posição do jogador, se necessário.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @return 0 para indicar que a função foi executada com sucesso.
 */
int	loop_hook(t_cub3d *cub3d)
{
	t_position			old_position;

	update_enemy_animation(cub3d);
	render_3d_view(cub3d);
	if (cub3d->mini_map_visible == true)
		render_mini_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win,
		cub3d->map_view.img, 0, 0);
	old_position = cub3d->player.position;
	update_possition_player(cub3d);
	if (check_colision(cub3d, cub3d->player.hitbox))
	{
		cub3d->player.position = find_new_position(cub3d->player.position,
				old_position, cub3d);
		cub3d->player.hitbox = define_hitbox(cub3d->player.position);
	}
	return (0);
}

/**
 * Verifica colisões com base na posição do jogador.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param hitbox A hitbox do jogador.
 * @return true se houver colisão, false caso contrário.
 */
bool	check_colision(t_cub3d *cub3d, t_hitbox hitbox)
{
	if (cub3d->map[(int)hitbox.bottom_left_corner.y]
		[(int)hitbox.bottom_left_corner.x] == '1')
		return (true);
	if (cub3d->map[(int)hitbox.bottom_right_corner.y]
		[(int)hitbox.bottom_right_corner.x] == '1')
		return (true);
	if (cub3d->map[(int)hitbox.top_left_corner.y]
		[(int)hitbox.top_left_corner.x] == '1')
		return (true);
	if (cub3d->map[(int)hitbox.top_right_corner.y]
		[(int)hitbox.top_right_corner.x] == '1')
		return (true);
	return (false);
}

/**
 * Encontra uma nova posição para o jogador.
 *
 * @param wanted_position A posição desejada.
 * @param old_position A posição atual.
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @return A nova posição do jogador.
 */
t_position	find_new_position(t_position wanted_position,
	t_position old_position, t_cub3d *cub3d)
{
	t_position	new_position;

	new_position.x = wanted_position.x;
	new_position.y = old_position.y;
	if (!check_colision(cub3d, define_hitbox(new_position)))
		return (new_position);
	new_position.x = old_position.x;
	new_position.y = wanted_position.y;
	if (!check_colision(cub3d, define_hitbox(new_position)))
		return (new_position);
	new_position.x = old_position.x;
	new_position.y = old_position.y;
	return (new_position);
}
