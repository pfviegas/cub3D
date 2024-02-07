/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:34:06 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/07 12:50:12 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
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
	cub3d->map_total_lines = i;
	cub3d->map = (char **)malloc(sizeof(char *) * (cub3d->map_total_lines + 2));
	if (!cub3d->map)
		quit("nError: Malloc error.", cub3d, 22);
	i = 0;
	start_line = cub3d->start_map;
	while (i < cub3d->map_total_lines)
		cub3d->map[i++] = ft_strdup(cub3d->cub[start_line++]);
	cub3d->map[i] = NULL;
}

void draw_bar(t_cub3d *cub3d, int x, int y, float angle) 
{
    int bar_x2;
    int bar_y2;
    int dx;
    int dy;
	int sx;
    int sy;
    int err;
	int e2;
	
	bar_x2 = x + BAR_LENGTH * cos(cub3d->player.dirx + angle);
	bar_y2 = y - BAR_LENGTH * -sin(cub3d->player.dirx + angle);
	dx = abs(bar_x2 - x);
	dy = abs(bar_y2 - y);
    err = dx - dy;
	if (x < bar_x2)
		sx = 1;
	else
		sx = -1;
	if (y < bar_y2)
		sy = 1;
	else
		sy = -1;
	while (1) 
	{
		my_pixel_put(&cub3d->map_view, x, y, get_argb(0,255, 0, 0));
		if (x == bar_x2 && y == bar_y2)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
    }
}
