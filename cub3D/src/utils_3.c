/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:45:49 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/20 14:50:09 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Obtém a cor de um pixel específico em uma imagem.
 *
 * @param img A estrutura de dados da imagem.
 * @param x A coordenada x do pixel.
 * @param y A coordenada y do pixel.
 * @return A cor do pixel.
 */
unsigned int	get_pixel_color(t_image_data *img, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

/**
 * Cria um valor inteiro representando uma cor ARGB.
 *
 * @param t O valor do canal de transparência (0-255).
 * @param r O valor do canal de vermelho (0-255).
 * @param g O valor do canal de verde (0-255).
 * @param b O valor do canal de azul (0-255).
 * @return O valor inteiro representando a cor ARGB.
 */
int	get_argb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * Função responsável por obter os dados da textura.
 * 
 * @param cub3d O ponteiro para a estrutura.
 *  
 * Calcula o passo da textura para desenhar uma parede em uma cena 3D.
 * A variável `cub3d->tex.step` é definida como a altura da textura 
 * (`TEXTURE_HEIGHT`) dividida pela altura da linha da parede 
 * (`cub3d->tex.wall_line_h`).
 * A expressão `(double)TEXTURE_HEIGHT / cub3d->tex.wall_line_h` calcula 
 * o passo da textura. Isso é feito para determinar quantos pixels da 
 * textura devem ser desenhados para cada pixel da linha da parede.
 * Se a altura da textura for maior que a altura da linha da parede, 
 * o passo da textura será menor que 1, o que significa que nem todos 
 * os pixels da textura serão desenhados. 
 * Se a altura da textura for menor que a altura da linha da parede, 
 * o passo da textura será maior que 1, o que significa que alguns 
 * pixels da textura serão desenhados várias vezes.
 * Isso garante que a textura seja desenhada corretamente na parede, 
 * independentemente da altura da textura ou da altura da linha da parede.
 */

void	get_tex_data(t_cub3d *cub3d)
{
	double	wall_x;

	cub3d->tex.tex_x = 0;
	cub3d->tex.tex_y = 0;
	if (cub3d->ray.wall_side == 0)
		wall_x = cub3d->player.position.y + cub3d->ray.perp_wall_dist 
			* cub3d->ray.ray_dir.y;
	else
		wall_x = cub3d->player.position.x + cub3d->ray.perp_wall_dist 
			* cub3d->ray.ray_dir.x;
	wall_x -= floor(wall_x);
	cub3d->tex.tex_x = wall_x * TEXTURE_WIDTH;
	if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x < 0)
		cub3d->tex.tex_x = TEXTURE_WIDTH - cub3d->tex.tex_x - 1;
	if (cub3d->ray.wall_side == 1 && cub3d->ray.ray_dir.y > 0)
		cub3d->tex.tex_x = TEXTURE_WIDTH - cub3d->tex.tex_x - 1;
	cub3d->tex.step = (double)TEXTURE_HEIGHT / cub3d->tex.wall_line_h;
}
