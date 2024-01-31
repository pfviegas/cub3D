/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:35:46 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 16:56:55 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// calcula a proxima coordenada quando a tecla para cima foi pressionada
void	move_up(t_cub3d *cub3d, float *col, float *line)
{
	*col = cub3d->player_xx + DISTANCE_MOVE * cos(cub3d->angle_direction * 3.14 / 180);
	*line = cub3d->player_yy - DISTANCE_MOVE * sin(cub3d->angle_direction * 3.14 / 180);
}

// calcula a proxima coordenada quando a tecla para baixo foi pressionada
void	move_down(t_cub3d *cub3d, float *col, float *line)
{
	*col = cub3d->player_xx - DISTANCE_MOVE * cos(cub3d->angle_direction * 3.14 / 180);
	*line = cub3d->player_yy + DISTANCE_MOVE * sin(cub3d->angle_direction * 3.14 / 180);
}

// calcula a proxima coordenada quando a tecla para a direita foi pressionada
void	move_right(t_cub3d *cub3d, float *col, float *line)
{
	*col = cub3d->player_xx + DISTANCE_MOVE * cos((cub3d->angle_direction + 90) * 3.14 / 180);
	*line = cub3d->player_yy - DISTANCE_MOVE * sin((cub3d->angle_direction + 90) * 3.14 / 180);	
}

// calcula a proxima coordenada quando a tecla para a esquerda foi pressionada
void	move_left(t_cub3d *cub3d, float *col, float *line)
{
	*col = cub3d->player_xx - DISTANCE_MOVE * cos((cub3d->angle_direction + 90) * 3.14 / 180);
	*line = cub3d->player_yy + DISTANCE_MOVE * sin((cub3d->angle_direction + 90) * 3.14 / 180);
}

// verifica se o jogador pode se mover para a nova posição, 
// considerando as regras do jogo (paredes, coletáveis, saídas, ...)
static int	valid_move(t_cub3d *cub3d, int col, int line, int pressed_key)
{
	printf("(valid move)Moves line: %d\n", line);
	printf("(valid move)Moves col: %d\n", col);
	printf("cub3d->map[%d][%d] = %c\n", line, col, cub3d->map[col][line]);
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
	// int	temp_col;
	// int	temp_line;

// 	if(col - round(col) > 0)
// 		temp_col = col - 0.15;
// 	else
// 		temp_col = col + 0.15;
// //PFV corrigir o line
// 	if(line - round(line) > 0)
// 		temp_line = line + 0.09;
// 	else
// 		temp_line = line - 0.15;
	printf("col = %f\n", col);
	printf("line = %f\n", line);
	valid = valid_move(cub3d, col, line, pressed_key);
	printf("valid = %d\n", valid);
	
	if (valid == 1)
	{
		cub3d->player_yy = line;
		cub3d->player_xx = col;
		printf("Moves: %d\n", cub3d->move++);
		printf("Moves XX: %f\n", cub3d->player_xx);
		printf("Moves YY: %f\n", cub3d->player_yy);
	
		render_map(cub3d);
	}
}

// trata os movimentos do jogador
int	key_handling(int keycode, t_cub3d *cub3d)
{
	float	col = 0;
	float	line = 0;
	
	col = cub3d->player_xx;
	line = cub3d->player_yy;
	if (keycode == A)
		move_right(cub3d, &col, &line);
	else if (keycode == W)
		move_up(cub3d, &col, &line);	
	else if (keycode == S)
		move_down(cub3d, &col, &line);
	else if (keycode == D)
		move_left(cub3d, &col, &line);
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
