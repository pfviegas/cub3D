/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:26 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 12:24:34 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// verifica recursivamente se é possível alcançar todos os coletáveis e a saída
// a partir da posição do jogador. 
bool	fill(t_cub3d *cub3d, char c, int line, int col)
{
	static bool		exit = false;
	static int		collectibles = 0;

	if (line < 0 || col < 0 || line >= cub3d->total_lines_map || col >= cub3d->column)
		return (false);
	else if (cub3d->map_floodfill[line][col] == 'X')
		return (false);
	else if (cub3d->map_floodfill[line][col] == '1')
		return (false);
	else if (cub3d->map_floodfill[line][col] == 'E')
		exit = true;
	if (cub3d->map_floodfill[line][col] == 'C')
		collectibles++;
	cub3d->map_floodfill[line][col] = 'X';
	fill(cub3d, c, line + 1, col);
	fill(cub3d, c, line, col + 1);
	fill(cub3d, c, line - 1, col);
	fill(cub3d, c, line, col - 1);
	return (collectibles == cub3d->collectibles && exit);
}

// verifica se é possível alcançar todos os coletáveis a partir 
// da posição do jogador. 
int	floodfill(t_cub3d *cub3d)
{
	char	seed;
	int		line;
	int		col;
	bool	valid;

	seed = cub3d->map_floodfill[cub3d->player_y][cub3d->player_x];
	line = cub3d->player_y;
	col = cub3d->player_x;
	valid = fill(cub3d, seed, line, col);
	return (valid);
}
