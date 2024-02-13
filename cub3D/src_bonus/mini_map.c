/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:37:45 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/13 17:34:17 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/**
 * Define as bordas do minimapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	set_mini_map_border(t_cub3d *cub3d)
{
	int	col;
	int	line;

	col = -1;
	line = -1;
	while (++line <= (MINIMAP_HEIGHT))
	{
		if (line == 0 || line == (MINIMAP_HEIGHT))
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
void	render_mini_map(t_cub3d *cub3d)
{
	int	line;
	int	col;
	int	mini_map_line;
	int	mini_map_col;

	line = (int)(cub3d->player.position.y - (MINIMAP_HEIGHT / (MINIMAP_SCALE * 2)) - 1);
	if (line < 0)
		line = -1;
	if (((int)cub3d->player.position.y > (int)((MINIMAP_HEIGHT / 2) / MINIMAP_SCALE)))
		mini_map_line = 0;
	else
		mini_map_line = abs((int)(cub3d->player.position.y - ((MINIMAP_HEIGHT / 2) / MINIMAP_SCALE)) - 1);
	while (cub3d->map[++line] && (mini_map_line * MINIMAP_SCALE) < MINIMAP_HEIGHT)
	{
		col = (int)(cub3d->player.position.x - (MINIMAP_WIDTH / (MINIMAP_SCALE * 2)) - 1);
		if (col < 0)
			col = -1;
		if (((int)cub3d->player.position.x > (int)((MINIMAP_WIDTH / 2) / MINIMAP_SCALE)))
			mini_map_col = 0;
		else
			mini_map_col = abs((int)(cub3d->player.position.x - ((MINIMAP_WIDTH / 2) / MINIMAP_SCALE)) - 1);
		while (cub3d->map[line][++col] && (mini_map_col * MINIMAP_SCALE) < MINIMAP_WIDTH)
		{
			if (col <= (int)ft_strlen(cub3d->map[line]))
				draw_mini_map(cub3d, &line, &col, &mini_map_line, &mini_map_col);
			mini_map_col++;
		}
		mini_map_line++;
	}
	set_mini_map_border(cub3d);
	draw_player(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2));
	draw_bar(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2), (-0.5));
	draw_bar(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2), (0.5));
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
void	draw_mini_map(t_cub3d *cub3d, int *line, int *col, int *mini_map_line, int *mini_map_col)
{
	int	floor_color;
	int	wall_color;
	int	player_color;

	floor_color = get_argb(0, cub3d->textures.floor_color[0], \
				cub3d->textures.floor_color[1], cub3d->textures.floor_color[2]);
	wall_color = get_argb(0, 27, 255, 30);
	player_color = get_argb(0, 228, 227, 225);
	if (cub3d->map[*line][*col] == '0')
		draw_square(cub3d, (*mini_map_col) * MINIMAP_SCALE, \
			(*mini_map_line) * MINIMAP_SCALE, floor_color);
	else if (cub3d->map[*line][*col] == '1')
		draw_square(cub3d, (*mini_map_col) * MINIMAP_SCALE, \
			(*mini_map_line) * MINIMAP_SCALE, wall_color);
	else if (cub3d->map[*line][*col] != '\n' && cub3d->map[*line][*col] != ' ')
		draw_square(cub3d, (*mini_map_col) * MINIMAP_SCALE, \
			(*mini_map_line) * MINIMAP_SCALE, player_color);
}
