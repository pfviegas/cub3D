/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:02 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 16:57:56 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// verifica se o programa foi chamado com o número correto de argumentos 
// e se o argumento fornecido tem a extensão .ber. 
void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Invalid number of argument.\n", 29);
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		write(2, "File must be of type .cub\n", 27);
		exit(2);
	}
}


void	check_elements(t_cub3d *cub3d, char *cl, int i)
{
	if (cl[i] == 'N' && cl[i + 1] == 'O' && ft_is_space(cl[i + 2]) == 1)
		cub3d->textures.north++;
	else if (cl[i] == 'S' && cl[i + 1] == 'O'  && ft_is_space(cl[i + 2]) == 1)
		cub3d->textures.south++;
	else if (cl[i] == 'W' && cl[i + 1] == 'E'  && ft_is_space(cl[i + 2]) == 1)
		cub3d->textures.west++;
	else if (cl[i] == 'E' && cl[i + 1] == 'A'  && ft_is_space(cl[i + 2]) == 1)
		cub3d->textures.east++;
	else if (cl[i] == 'F' && ft_is_space(cl[i + 1]) == 1)
		cub3d->textures.floor++;
	else if (cl[i] == 'C' && ft_is_space(cl[i + 1]) == 1)
		cub3d->textures.ceiling++;
}

void	check_number_elem(t_cub3d *cub3d)
{
	printf("cub3d->textures.north: %d\n", cub3d->textures.north);
	printf("cub3d->textures.north: %d\n", cub3d->textures.south);
	printf("cub3d->textures.north: %d\n", cub3d->textures.west);
	printf("cub3d->textures.north: %d\n", cub3d->textures.east);
	printf("cub3d->textures.north: %d\n", cub3d->textures.floor);
	printf("cub3d->textures.north: %d\n", cub3d->textures.ceiling);
	if (cub3d->textures.north != 1)
		quit("Error: Invalid element line.", cub3d, 5);
	if (cub3d->textures.south != 1)
		quit("Error: Invalid element line.", cub3d, 6);
	if (cub3d->textures.west != 1)
		quit("Error: Invalid element line.", cub3d, 7);
	if (cub3d->textures.east != 1)
		quit("Error: Invalid element line.", cub3d, 8);
	if (cub3d->textures.floor != 1)
		quit("Error: Invalid element line.", cub3d, 9);
	if (cub3d->textures.ceiling != 1)
		quit("Error: Invalid element line.", cub3d, 10);
}




// verifica se o mapa do jogo cumpre com as condições necessárias.
void	check_map(t_cub3d *cub3d)
{
	int	line;
	int	col;

	line = 0;
	while (cub3d->map[line] != NULL)
	{
		col = -1;
		while (cub3d->map[line][++col])
			check_char(cub3d, cub3d->map[line][col], line, col);
		line++;
	}
	if (line == col)
		quit("The map must be rectangular.", cub3d, 6);
	if (cub3d->collectibles == 0)
		quit("There's no collectibles.", cub3d, 7);
	else if (cub3d->exit == 0)
		quit("There's no exit.", cub3d, 8);
	else if (cub3d->exit > 1)
		quit("Just one exit per map.", cub3d, 9);
	else if (cub3d->player == 0)
		quit("There's no player.", cub3d, 10);
	else if (cub3d->player > 1)
		quit("Just one player per map.", cub3d, 11);
}

// soma os collectibles e verifica se os caracteres sao validos 
void	check_char(t_cub3d *cub3d, char c, int line, int col)
{
	if (c == 'C')
		cub3d->collectibles++;
	else if (c == 'E')
		cub3d->exit++;
	else if (c == 'P')
	{
		cub3d->player++;
		cub3d->player_x = col;
		cub3d->player_y = line;
	}
	else if (c == '1' || c == '0')
		return ;
	else
		quit("Invalid characters.", cub3d, 5);
}

// verifica se o mapa está cercado por paredes.
void	check_walls(t_cub3d *cub3d)
{
	int	line;
	int	col;

	line = 0;
	while (cub3d->map[line])
	{
		col = 0;
		while (cub3d->map[line][col])
		{
			if (cub3d->map[0][col] != '1' ||
				cub3d->map[cub3d->total_lines_map - 1][col] != '1')
				quit("The map is not surrounded by walls", cub3d, 12);
			if (cub3d->map[line][0] != '1' ||
				cub3d->map[line][cub3d->column - 1] != '1')
				quit("The map is not surrounded by walls", cub3d, 12);
			col++;
		}
		line++;
	}
}

// verifica se o caminho do jogador é válido.
void	check_path(t_cub3d *cub3d)
{
	if (!floodfill(cub3d))
	{
		quit("Invalid path on the map", cub3d, 13);
	}
	free_map_floodfill(cub3d);
}
