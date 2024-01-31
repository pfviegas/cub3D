/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:34:06 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 15:29:55 by pveiga-c         ###   ########.fr       */
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
	cub3d->map_total_lines = i;
	cub3d->map = (char **)malloc(sizeof(char *) * (cub3d->map_total_lines + 2));
	cub3d->map_floodfill = (char **)malloc(sizeof(char *) * (cub3d->map_total_lines + 2));
	if (!cub3d->map || !cub3d->map_floodfill)
		quit("nError: Malloc error.", cub3d, 22);
	i = 0;
	start_line = cub3d->start_map;
	while (i < cub3d->map_total_lines)
	{
		cub3d->map_floodfill[i] = ft_strdup(cub3d->cub[start_line]);
		cub3d->map[i++] = ft_strdup(cub3d->cub[start_line++]);
	}
	cub3d->map[i] = NULL;
	cub3d->map_floodfill[i] = NULL;
}


// renderiza o mapa
int	render_map(t_cub3d *cub3d)
{
	int	y;
	int	x;

	y = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			put_map(x, y, cub3d->map[y][x], cub3d);
			x++;
		}
		y++;
	}
	draw_player(cub3d->mlx, cub3d->win, cub3d->player_xx * 16, cub3d->player_yy * 16);
	draw_bar(cub3d, cub3d->player_xx * IMAGE_WIDTH, cub3d->player_yy * IMAGE_WIDTH + 3);

	return (0);
}

void draw_bar(t_cub3d *cub3d, int x, int y) 
{
    // Calcular as extremidades da barra com base no ângulo
    int bar_x1 = x;
    int bar_y1 = y;
    int bar_x2 = x + BAR_LENGTH * cos(cub3d->angle_direction * 3.14 / 180);
    int bar_y2 = y - BAR_LENGTH * sin(cub3d->angle_direction * 3.14 / 180);

    // Desenhar a linha que representa a barra
    int dx = abs(bar_x2 - bar_x1);
    int dy = abs(bar_y2 - bar_y1);
    int sx = (bar_x1 < bar_x2) ? 1 : -1;
    int sy = (bar_y1 < bar_y2) ? 1 : -1;
    int err = dx - dy;

    while (1) 
	{
        mlx_pixel_put(cub3d->mlx, cub3d->win, bar_x1, bar_y1, 0xFF0000);

        if (bar_x1 == bar_x2 && bar_y1 == bar_y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            bar_x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            bar_y1 += sy;
        }
    }
}
