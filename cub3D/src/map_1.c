/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:35:05 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/27 11:31:41 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Função responsável por obter as informações dos elementos do mapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param fd O descritor de arquivo do mapa.
 */
void get_elements_info(t_cub3d *cub3d)
{
	int line;
	int col;

	line = 0;
	col = 0;
	while(cub3d->cub[line] && is_start_map(cub3d->cub[line]) == 0)
	{
		col = 0;
		while (cub3d->cub[line][col] && is_space(cub3d->cub[line][col]) == 1)
			col++;
		check_elements(cub3d, cub3d->cub[line], col);
		line++;
	}
	if (is_start_map(cub3d->cub[line]) == 1)
		cub3d->start_map = line;
	if (line == 0)
		quit("nError: file empty.", cub3d, 7);
	else if (cub3d->start_map == 0)
		quit("nError: Invalid map start.", cub3d, 8);
}

// verifica se existem linhas em branco no meio do mapa
void	check_nl_middle_map(t_cub3d *cub3d)
{
	int		lines;
	int		flag;

	flag = 0;
	lines = cub3d->start_map;
	while (cub3d->cub[lines])
	{
		if (flag == 0 && cub3d->cub[lines][0] == '\0')
			flag = 1;
		if (flag == 1 && cub3d->cub[lines][0] != '\0')
			flag = 2;
		lines++;
	}
	if (flag == 2)
	{
		quit("nError: Invalid map.", cub3d, 19);
	}
	if (lines == cub3d->start_map )
		quit("nError: The map is empty.", cub3d, 20);
	else if (lines == cub3d->start_map + 1)
		quit("nError: Invalid map.", cub3d, 21);
}

// armazena o mapa
void	get_map(t_cub3d *cub3d)
{
	int		i;
	int		start_line;

	check_nl_middle_map(cub3d);
	i = 0;
	start_line = cub3d->start_map;
	while (cub3d->cub[start_line] && cub3d->cub[start_line][0] != '\0')
	{
		i++;
		start_line++;
	}
	cub3d->total_lines_map = i;
	cub3d->map = (char **)malloc(sizeof(char *) * (cub3d->total_lines_map + 2));
	if (!cub3d->map)
		quit("nError: Malloc error.", cub3d, 22);
	i = 0;
	start_line = cub3d->start_map;
	while (i < cub3d->total_lines_map)
	{
		cub3d->map[i++] = ft_strdup(cub3d->cub[start_line++]);
	}
	cub3d->map[i] = NULL;
}

/*
// renderiza o mapa
int	render_map(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	s;

	s = 64;
	if (cub3d->collectibles == 0)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->img.exit);
//		cub3d->img.exit = mlx_xpm_file_to_image(cub3d->mlx, PORTAL, &s, &s);
	}
	y = 0;
	while (y < cub3d->total_lines_map)
	{
		x = 0;
		while (x < cub3d->column)
		{
			put_map(x, y, cub3d->map[y][x], cub3d);
			x++;
		}
		y++;
	}
	return (0);
}
*/
