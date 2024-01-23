/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:02 by pviegas           #+#    #+#             */
/*   Updated: 2023/08/29 13:16:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// verifica se o programa foi chamado com o número correto de argumentos 
// e se o argumento fornecido tem a extensão .ber. 
void	check_args(t_game *game, int argc, char **argv)
{
	if (argc != 2)
	{
		quit("Invalid number of argument.", game, 1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
	{
		quit("File must be of type .ber", game, 2);
	}
}

// verifica se o mapa do jogo cumpre com as condições necessárias.
void	check_map(t_game *game)
{
	int	line;
	int	col;

	line = 0;
	while (game->map[line] != NULL)
	{
		col = -1;
		while (game->map[line][++col])
			check_char(game, game->map[line][col], line, col);
		line++;
	}
	if (line == col)
		quit("The map must be rectangular.", game, 6);
	if (game->collectibles == 0)
		quit("There's no collectibles.", game, 7);
	else if (game->exit == 0)
		quit("There's no exit.", game, 8);
	else if (game->exit > 1)
		quit("Just one exit per map.", game, 9);
	else if (game->player == 0)
		quit("There's no player.", game, 10);
	else if (game->player > 1)
		quit("Just one player per map.", game, 11);
}

// soma os collectibles e verifica se os caracteres sao validos 
void	check_char(t_game *game, char c, int line, int col)
{
	if (c == 'C')
		game->collectibles++;
	else if (c == 'E')
		game->exit++;
	else if (c == 'P')
	{
		game->player++;
		game->player_x = col;
		game->player_y = line;
	}
	else if (c == '1' || c == '0')
		return ;
	else
		quit("Invalid characters.", game, 5);
}

// verifica se o mapa está cercado por paredes.
void	check_walls(t_game *game)
{
	int	line;
	int	col;

	line = 0;
	while (game->map[line])
	{
		col = 0;
		while (game->map[line][col])
		{
			if (game->map[0][col] != '1' ||
				game->map[game->line - 1][col] != '1')
				quit("The map is not surrounded by walls", game, 12);
			if (game->map[line][0] != '1' ||
				game->map[line][game->column - 1] != '1')
				quit("The map is not surrounded by walls", game, 12);
			col++;
		}
		line++;
	}
}

// verifica se o caminho do jogador é válido.
void	check_path(t_game *game)
{
	if (!floodfill(game))
	{
		quit("Invalid path on the map", game, 13);
	}
	free_map_floodfill(game);
}
