/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:34:06 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/08 12:28:13 by pviegas          ###   ########.fr       */
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

/**
 * Função responsável por obter o mapa do jogo.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void get_map(t_cub3d *cub3d)
{
	int i;
	int start_line;

	check_nl_middle_map(cub3d);
	i = 0;
	start_line = cub3d->start_map;
	// Conta o número total de linhas do mapa
	while (cub3d->cub[start_line] && cub3d->cub[start_line][0] != '\0')
	{
		i++;
		start_line++;
	}
	cub3d->map_total_lines = i;
	// Aloca memória para o mapa
	cub3d->map = (char **)malloc(sizeof(char *) * (cub3d->map_total_lines + 2));
	if (!cub3d->map)
		quit("nError: Malloc error.", cub3d, 22);
	i = 0;
	start_line = cub3d->start_map;
	// Copia as linhas do mapa para a estrutura do jogo
	while (i < cub3d->map_total_lines)
		cub3d->map[i++] = ft_strdup(cub3d->cub[start_line++]);
	cub3d->map[i] = NULL;
}

void	draw_bar(t_cub3d *cub3d, int x, int y, float angle)
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
    err = abs(bar_x2 - x) - dy;
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

