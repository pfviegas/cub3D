/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:35:46 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 12:32:02 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// verifica se o jogador pode se mover para a nova posição, 
// considerando as regras do jogo (paredes, coletáveis, saídas, ...)
static int	valid_move(t_cub3d *cub3d, int col, int line, int pressed_key)
{
	printf("Moves line: %d\n", line);
	printf("Moves col: %d\n", col);
	cub3d->temp = '0';
	if (cub3d->map[line][col] == '1')
		return (-1);
	if (pressed_key != W && pressed_key != ARROW_UP 
		&& pressed_key != S && pressed_key != ARROW_DOWN
		&& pressed_key != A && pressed_key != ARROW_LEFT
		&& pressed_key != D && pressed_key != ARROW_RIGHT)
		return (-1);
	else
		return (1);
}

// valida o movimento do jogador, atualiza as posições no mapa, 
// gere a recolha dos coletáveis e a saída, e atualiza a 
// renderização do mapa após cada movimento.
static void	move_player(t_cub3d *cub3d, float col, float line, int pressed_key)
{
	int	valid;
	int	temp_col;
	int	temp_line;

	if(col - round(col) > 0)
		temp_col = col - 0.15;
	else
		temp_col = col + 0.15;
//PFV corrigir o line
	if(line - round(line) > 0)
		temp_line = line + 0.09;
	else
		temp_line = line - 0.15;
	valid = valid_move(cub3d, temp_col, temp_line, pressed_key);
	if (valid == 1)
	{
		cub3d->player_yy = line;
		cub3d->player_xx = col;
		//cub3d->map[int(line)][int(col)] = 'N';
		//cub3d->map[temp_line][temp_col] = '0';
		printf("Moves: %d\n", cub3d->move++);
		printf("Moves XX: %f\n", cub3d->player_xx);
		printf("Moves YY: %f\n", cub3d->player_yy);
	
		render_map(cub3d);
	}
}

// trata os movimentos do jogador
int	key_handling(int keycode, t_cub3d *cub3d)
{
	float	col;
	float	line;

	col = cub3d->player_xx;
	line = cub3d->player_yy;
	if ((keycode == A) && cub3d->player_xx != cub3d->player_x)
		col = col - DISTANCE_MOVE;
	else if (keycode == W || keycode == ARROW_UP)
		line = line - DISTANCE_MOVE;
	else if (keycode == S || keycode == ARROW_DOWN)
		line = line + DISTANCE_MOVE;
	else if (keycode == D)
		col = col + DISTANCE_MOVE;
	else if (keycode == ESC)
		exit_cub3d(cub3d);
	else if (keycode == ARROW_LEFT)
		cub3d->angle_direction += ROTATION_MOVE;
	else if (keycode == ARROW_RIGHT)
		cub3d->angle_direction -= ROTATION_MOVE;
	if(cub3d->angle_direction > 360)
		cub3d->angle_direction = 0;
	else if(cub3d->angle_direction < 0)
		cub3d->angle_direction = 360;
	move_player(cub3d, col, line, keycode);
	return (0);
}
