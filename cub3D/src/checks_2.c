/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:58:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/08 12:42:32 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/**
 * Verifica se os arquivos das imagens das texturas especificadas no 
 * struct `textures` existem. Caso algum arquivo esteja faltando, 
 * a função exibe uma mensagem de erro correspondente e encerra o programa.
 *
 * @param cub3d O ponteiro para a estrutura `t_cub3d`.
 */
void	check_textures_images(t_cub3d *cub3d)
{
	int	fd;

	fd = open(cub3d->textures.north_path, O_RDONLY);
	if (fd == -1)
		quit("nError: North image missing.", cub3d, 15);
	close(fd);
	fd = open(cub3d->textures.south_path, O_RDONLY);
	if (fd == -1)
		quit("nError: South image missing.", cub3d, 16);
	close(fd);
	fd = open(cub3d->textures.west_path, O_RDONLY);
	if (fd == -1)
		quit("nError: West image missing.", cub3d, 17);
	close(fd);
	fd = open(cub3d->textures.east_path, O_RDONLY);
	if (fd == -1)
		quit("nError: East image missing.", cub3d, 18);
	close(fd);
}

/**
 * Verifica se o mapa está fechado por paredes. Caso o mapa não esteja 
 * fechado corretamente, a função exibe uma mensagem de erro correspondente 
 * e encerra o programa.
 *
 * @param cub3d O ponteiro para a estrutura `t_cub3d`.
 */
void	check_map(t_cub3d *cub3d)
{
	int	line;
	int	col;

	line = 0;
	while (cub3d->map[line] != NULL)
	{
		col = 0;
		while (cub3d->map[line][col] == ' ')
			col++;
		while (cub3d->map[line][col])
		{
			check_char(cub3d, cub3d->map[line][col], line, col);
			col++;
		}
		if (cub3d->map_max_column < col)
			cub3d->map_max_column = col;
		line++;
	}
	if (cub3d->player_number == 0)
		quit("nError: There's no player.", cub3d, 25);
	else if (cub3d->player_number > 1)
		quit("nError: Just one player per map.", cub3d, 26);
}

/**
 * Verifica se o caractere `c` é válido. Caso o caractere não seja válido, 
 * a função exibe uma mensagem de erro correspondente e encerra o programa.
 *
 * @param cub3d O ponteiro para a estrutura `t_cub3d`.
 * @param c O caractere a ser verificado.
 * @param line A linha onde o caractere foi encontrado.
 * @param col A coluna onde o caractere foi encontrado.
 */
void	check_char(t_cub3d *cub3d, char c, int line, int col)
{
	if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		cub3d->player_number++;
		cub3d->player.position.y = line + 0.5;
		cub3d->player.position.x = col + 0.5;
		cub3d->player_direction = c;
		if(c == 'N')
			cub3d->player.dirx = 3 * MY_PI_2;
		if(c == 'S')
			cub3d->player.dirx = MY_PI_2;
		if(c == 'W')
			cub3d->player.dirx = MY_PI;
		if(c == 'E')
			cub3d->player.dirx = 0;
	}
	else if (c == '0' || c == '1')
		return ;
	else if (c == ' ')
		is_surrounded_1(cub3d, line, col);
	else
		quit("nError: Invalid characters.", cub3d, 23);
}

/**
 * Verifica se o caractere `c` está cercado por paredes. Caso o caractere 
 * não esteja cercado corretamente, a função exibe uma mensagem de erro 
 * correspondente e encerra o programa.
 *
 * @param cub3d O ponteiro para a estrutura `t_cub3d`.
 * @param line A linha onde o caractere foi encontrado.
 * @param col A coluna onde o caractere foi encontrado.
 */
void	check_map_surrounded_end(t_cub3d *cub3d)
{
	int i;
	int j_0;
	int j_1;

	i = 0;
	while(cub3d->map[++i])
	{
		j_0 = (size_t)(ft_strlen(cub3d->map[i - 1]) - 1);
		j_1 = (size_t)(ft_strlen(cub3d->map[i]) - 1);
		while (j_0 > 0 && cub3d->map[i -1][j_0] == ' ')
			j_0--;
		while (j_1 > 0 && cub3d->map[i][j_1] == ' ')
			j_1--;
		if(j_0 < j_1)
		{	
			while(cub3d->map[i][j_0])
				if(cub3d->map[i][j_0++] == '0')
					quit("nError: Invalid Map.", cub3d, 34);
		}
		else if (j_0 > j_1)
			while(cub3d->map[i - 1][j_1])
				if(cub3d->map[i - 1][j_1++] == '0')
					quit("nError: Invalid Map.", cub3d, 35);
	}
}

void	check_map_surrounded_start(t_cub3d *cub3d)
{
	int i;
	int j_0;
	int j_1;

	i = 0;
	while(cub3d->map[++i])
	{
		j_0 = 0;
		j_1 = 0;
		while (cub3d->map[i -1][j_0] == ' ')
			j_0++;
		while (cub3d->map[i][j_1] == ' ')
			j_1++;
		if(j_0 > j_1)
		{		
			while(j_1 <= j_0)
				if(cub3d->map[i][j_1++] == '0')	
					quit("nError: Invalid Map.", cub3d, 36);
		}
		else if (j_0 < j_1)
			while(j_0 <= j_1)
				if(cub3d->map[i - 1][j_0++] == '0')
					quit("nError: Invalid Map.", cub3d, 37);
	}
}
