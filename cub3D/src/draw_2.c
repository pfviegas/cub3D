/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:33:22 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/14 12:40:32 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Função responsável por desenhar um pixel na imagem.
 *
 * @param img A estrutura de dados da imagem.
 * @param x A coordenada x do pixel.
 * @param y A coordenada y do pixel.
 * @param color A cor do pixel.
 */
void	my_pixel_put(t_image_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * Desenha uma parede na posição especificada na tela.
 *
 * @param cub3d O ponteiro para a estrutura.
 * @param pixel_w A coordenada x do pixel na tela.
 * @param pixel_h A coordenada y do pixel na tela.
 */

void	draw_wall(t_cub3d *cub3d, int pixel_w, int pixel_h)
{
	cub3d->tex.tex_y = abs((int)(((float)pixel_h - (float)SCREEN_HEIGHT / 2.0
					+ (float)cub3d->tex.wall_line_h / 2.0) * cub3d->tex.step));
	if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x > 0)
		cub3d->tex.color = get_pixel_color(&cub3d->east_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	else if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x < 0)
		cub3d->tex.color = get_pixel_color(&cub3d->west_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	else if (cub3d->ray.wall_side == 1 && cub3d->ray.ray_dir.y > 0)
		cub3d->tex.color = get_pixel_color(&cub3d->south_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	else
		cub3d->tex.color = get_pixel_color(&cub3d->north_view, cub3d->tex.tex_x,
				cub3d->tex.tex_y);
	my_pixel_put(&cub3d->map_view, pixel_w, pixel_h, cub3d->tex.color);
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
void	draw_mini_map(t_cub3d *cub3d, t_mini_map *mini_map)
{
	int	floor_color;
	int	wall_color;
	int	player_color;

	floor_color = get_argb(0, cub3d->textures.floor_color[0], \
				cub3d->textures.floor_color[1], \
				cub3d->textures.floor_color[2]);
	wall_color = get_argb(0, 27, 255, 30);
	player_color = get_argb(0, 228, 227, 225);
	if (cub3d->map[mini_map->map_line][mini_map->map_col] == '0')
		draw_square(cub3d, (mini_map->mini_map_col) * MINIMAP_SCALE, \
			(mini_map->mini_map_line) * MINIMAP_SCALE, floor_color);
	else if (cub3d->map[mini_map->map_line][mini_map->map_col] == '1')
		draw_square(cub3d, (mini_map->mini_map_col) * MINIMAP_SCALE, \
			(mini_map->mini_map_line) * MINIMAP_SCALE, wall_color);
	else if (cub3d->map[mini_map->map_line][mini_map->map_col] != '\n' && \
		cub3d->map[mini_map->map_line][mini_map->map_col] != ' ')
		draw_square(cub3d, (mini_map->mini_map_col) * MINIMAP_SCALE, \
				(mini_map->mini_map_line) * MINIMAP_SCALE, player_color);
}

/**
 * Define as bordas do minimapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	draw_mini_map_border(t_cub3d *cub3d)
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
