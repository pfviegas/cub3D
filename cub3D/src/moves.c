/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:03:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/09/01 12:03:17 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// verifica se o jogador pode se mover para a nova posição, 
// considerando as regras do jogo (paredes, coletáveis, saídas, ...)
static int	valid_move(t_game *game, int col, int line, int pressed_key)
{
	game->temp = '0';
	if (game->map[line][col] == '1')
		return (-1);
	if (game->map[line][col] == 'C')
		game->collectibles--;
	if (game->map[line][col] == 'E' && game->collectibles > 0)
	{
		game->player_on_exit = 1;
		game->temp = 'O';
		return (1);
	}
	if (game->map[line][col] == 'E' && game->collectibles == 0)
	{
		game->end_game = 1;
		ft_printf("Moves: %d\n", game->move++);
		ft_printf("\n\n\t\tCongrats!!!\tYOU WIN (*_*)\n\n");
		exit_game(game);
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
static void	move_player(t_game *game, int col, int line, int pressed_key)
{
	int	valid;
	int	temp_col;
	int	temp_line;

	temp_col = game->player_x;
	temp_line = game->player_y;
	valid = valid_move(game, col, line, pressed_key);
	if (valid != -1)
	{
		game->player_y = line;
		game->player_x = col;
		if (game->temp != 'O')
			game->map[line][col] = 'P';
		else
			game->map[line][col] = 'O';
		if (game->map[temp_line][temp_col] != 'O')
			game->map[temp_line][temp_col] = '0';
		else
			game->map[temp_line][temp_col] = 'E';
		ft_printf("Moves: %d\n", game->move++);
		render_map(game);
	}
}

// trata os movimentos do jogador
int	key_handling(int keycode, t_game *game)
{
	int	col;
	int	line;

	col = game->player_x;
	line = game->player_y;
	if (keycode == A || keycode == ARROW_LEFT)
		col--;
	else if (keycode == W || keycode == ARROW_UP)
		line--;
	else if (keycode == S || keycode == ARROW_DOWN)
		line++;
	else if (keycode == D || keycode == ARROW_RIGHT)
		col++;
	else if (keycode == ESC)
		exit_game(game);
	if (game->end_game != 1)
		move_player(game, col, line, keycode);
	return (0);
}
