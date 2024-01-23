/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:03:15 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 12:23:45 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// verifica se o jogador pode se mover para a nova posição, 
// considerando as regras do jogo (paredes, coletáveis, saídas, ...)
static int	valid_move(t_cub3d *cub3d, int col, int line, int pressed_key)
{
	cub3d->temp = '0';
	if (cub3d->map[line][col] == '1')
		return (-1);
	if (cub3d->map[line][col] == 'C')
		cub3d->collectibles--;
	if (cub3d->map[line][col] == 'E' && cub3d->collectibles > 0)
	{
		cub3d->player_on_exit = 1;
		cub3d->temp = 'O';
		return (1);
	}
	if (cub3d->map[line][col] == 'E' && cub3d->collectibles == 0)
	{
		cub3d->end_cub3d = 1;
		ft_printf("Moves: %d\n", cub3d->move++);
		ft_printf("\n\n\t\tCongrats!!!\tYOU WIN (*_*)\n\n");
		exit_cub3d(cub3d);
	}
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
static void	move_player(t_cub3d *cub3d, int col, int line, int pressed_key)
{
	int	valid;
	int	temp_col;
	int	temp_line;

	temp_col = cub3d->player_x;
	temp_line = cub3d->player_y;
	valid = valid_move(cub3d, col, line, pressed_key);
	if (valid != -1)
	{
		cub3d->player_y = line;
		cub3d->player_x = col;
		if (cub3d->temp != 'O')
			cub3d->map[line][col] = 'P';
		else
			cub3d->map[line][col] = 'O';
		if (cub3d->map[temp_line][temp_col] != 'O')
			cub3d->map[temp_line][temp_col] = '0';
		else
			cub3d->map[temp_line][temp_col] = 'E';
		ft_printf("Moves: %d\n", cub3d->move++);
		render_map(cub3d);
	}
}

// trata os movimentos do jogador
int	key_handling(int keycode, t_cub3d *cub3d)
{
	int	col;
	int	line;

	col = cub3d->player_x;
	line = cub3d->player_y;
	if (keycode == A || keycode == ARROW_LEFT)
		col--;
	else if (keycode == W || keycode == ARROW_UP)
		line--;
	else if (keycode == S || keycode == ARROW_DOWN)
		line++;
	else if (keycode == D || keycode == ARROW_RIGHT)
		col++;
	else if (keycode == ESC)
		exit_cub3d(cub3d);
	if (cub3d->end_cub3d != 1)
		move_player(cub3d, col, line, keycode);
	return (0);
}
