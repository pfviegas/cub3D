/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:33:22 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/09 15:44:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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
