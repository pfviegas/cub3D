/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:34:06 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/09 15:44:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/**
 * Função responsável por obter as informações dos elementos do mapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param fd O descritor de arquivo do mapa.
 */
void	get_elements_info(t_cub3d *cub3d)
{
	int	line;
	int	col;

	line = 0;
	col = 0;
	while (cub3d->cub[line] && is_start_map(cub3d->cub[line]) == 0)
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
void	get_map(t_cub3d *cub3d)
{
	int	i;
	int	start_line;

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
