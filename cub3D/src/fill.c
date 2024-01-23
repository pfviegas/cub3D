/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:26 by pviegas           #+#    #+#             */
/*   Updated: 2023/09/01 12:03:26 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// verifica recursivamente se é possível alcançar todos os coletáveis e a saída
// a partir da posição do jogador. 
bool	fill(t_game *game, char c, int line, int col)
{
	static bool		exit = false;
	static int		collectibles = 0;

	if (line < 0 || col < 0 || line >= game->line || col >= game->column)
		return (false);
	else if (game->map_floodfill[line][col] == 'X')
		return (false);
	else if (game->map_floodfill[line][col] == '1')
		return (false);
	else if (game->map_floodfill[line][col] == 'E')
		exit = true;
	if (game->map_floodfill[line][col] == 'C')
		collectibles++;
	game->map_floodfill[line][col] = 'X';
	fill(game, c, line + 1, col);
	fill(game, c, line, col + 1);
	fill(game, c, line - 1, col);
	fill(game, c, line, col - 1);
	return (collectibles == game->collectibles && exit);
}

// verifica se é possível alcançar todos os coletáveis a partir 
// da posição do jogador. 
int	floodfill(t_game *game)
{
	char	seed;
	int		line;
	int		col;
	bool	valid;

	seed = game->map_floodfill[game->player_y][game->player_x];
	line = game->player_y;
	col = game->player_x;
	valid = fill(game, seed, line, col);
	return (valid);
}
