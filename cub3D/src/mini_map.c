/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:37:45 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/12 16:36:32 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Função responsável por obter o mini mapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void get_mini_map(t_cub3d *cub3d)
{
	int m_y;
	int map_pos_y;

	m_y = (int)cub3d->player.position.y - 6;
	map_pos_y = 10;
	while (m_y <= (int)cub3d->player.position.y + 5 && m_y < cub3d->map_total_lines)
	{
		if (m_y >= 0)
			printf("teste\n");
		// get_map_around_loop(map_pos_y, map, m_y);
		map_pos_y += 18;
		m_y++;
	}
}

/**
 * Define as bordas do minimapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void set_borders(t_cub3d *cub3d)
{
	int col;
	int line;

	col = -1;
	line = -1;
	while (++line <= MINIMAP_HEIGHT)
	{
		if (line == 0 || line == MINIMAP_HEIGHT)
		{
			while (++col <= MINIMAP_WIDTH)
				my_pixel_put(&cub3d->map_view, col, line, 0x000000);
			col = -1;
		}
		my_pixel_put(&cub3d->map_view, 0, line, 0x000000);
		my_pixel_put(&cub3d->map_view, MINIMAP_WIDTH, line, 0x000000);
	}
}

/**
 * Renderiza o minimapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void render_mini_map(t_cub3d *cub3d)
{
	int line;
	int col;
	int mini_map_line;
	int mini_map_col;
	
//	line = -1;
	line = (int)(cub3d->player.position.y - (MINIMAP_HEIGHT / (MINIMAP_SCALE * 2)) - 1);
	if (line < 0)
		line = -1;

	mini_map_line = 0;
//	while (cub3d->map[++line])
	while (cub3d->map[++line] && (mini_map_line * MINIMAP_SCALE) < MINIMAP_HEIGHT)
	{
		col = (int)(cub3d->player.position.x - (MINIMAP_WIDTH / (MINIMAP_SCALE * 2)) - 1);
		if (col < 0)
			col = -1;
		mini_map_col = 0;
		while (cub3d->map[line][++col] && (mini_map_col * MINIMAP_SCALE) < MINIMAP_WIDTH)
		{
			draw_mini_map(cub3d, &line, &col, &mini_map_line, &mini_map_col);
			mini_map_col++;	
		}
		mini_map_line++;
	}
	set_borders(cub3d);
//	get_mini_map(cub3d);
	draw_player(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2));
	draw_bar(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2), (-0.5));
	draw_bar(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2), (0.5));
//	draw_player(cub3d, (cub3d->player.position.x * MINIMAP_SCALE),
//				(cub3d->player.position.y * MINIMAP_SCALE));
	// draw_bar(cub3d, (cub3d->player.position.x) * MINIMAP_SCALE,
	// 		 (cub3d->player.position.y) * MINIMAP_SCALE, (-0.5));
	// draw_bar(cub3d, (cub3d->player.position.x) * MINIMAP_SCALE,
	// 		 (cub3d->player.position.y) * MINIMAP_SCALE, (0.5));
}

/**
 * Desenha o mini mapa do jogo.
 * 
 * Desenha o mini mapa do jogo com base na matriz de caracteres que representa
 * o mapa. Cada caractere na matriz é mapeado para uma cor específica e 
 * desenhado como um quadrado no mini mapa.
 * 
 * @param cub3d O ponteiro para a estrutura do jogo cub3d.
 * @param line O ponteiro para a posição atual da linha na matriz do mapa.
 * @param col O ponteiro para a posição atual da coluna na matriz do mapa.
 */
void draw_mini_map(t_cub3d *cub3d, int *line, int *col, int *mini_map_line, int *mini_map_col)
{
	if (cub3d->map[*line][*col] == '0')
		draw_square(cub3d, (*mini_map_col) * MINIMAP_SCALE, (*mini_map_line) * MINIMAP_SCALE,
					get_argb(0, cub3d->textures.floor_color[0],
							 cub3d->textures.floor_color[1],
							 cub3d->textures.floor_color[2]));
	else if (cub3d->map[*line][*col] == '1')
		draw_square(cub3d, (*mini_map_col) * MINIMAP_SCALE, (*mini_map_line) * MINIMAP_SCALE,
					get_argb(0, 27, 255, 30));
	else if (cub3d->map[*line][*col] != '\n' && cub3d->map[*line][*col] != ' ')
		draw_square(cub3d, (*mini_map_col) * MINIMAP_SCALE, (*mini_map_line) * MINIMAP_SCALE,
					get_argb(0, 228, 227, 225));
}
