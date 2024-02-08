/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:33:22 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/08 15:47:16 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Desenha a barra do FOV do jogador.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * @param x A coordenada x do ponto de origem da barra.
 * @param y A coordenada y do ponto de origem da barra.
 * @param angle O ângulo em radianos para a direção da barra.
 */
void	draw_bar(t_cub3d *cub3d, int x, int y, float angle)
{
	t_bar draw;

	draw.bar_x2 = x + BAR_LENGTH * cos(cub3d->player.dirx + angle);
	draw.bar_y2 = y - BAR_LENGTH * -sin(cub3d->player.dirx + angle);
	draw.dx = abs(draw.bar_x2 - x);
	draw.dy = abs(draw.bar_y2 - y);
	draw.err = draw.dx - draw.dy;
	if (x < draw.bar_x2)
		draw.sx = 1;
	else
		draw.sx = -1;
	if (y < draw.bar_y2)
		draw.sy = 1;
	else
		draw.sy = -1;
	draw_bar_2(cub3d, draw, x, y);
}

/**
 * Desenha uma barra na tela usando o algoritmo de Bresenham.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * @param draw A estrutura que contém as informações necessárias para desenhar a barra.
 * @param x A coordenada x inicial do ponto de partida da barra.
 * @param y A coordenada y inicial do ponto de partida da barra.
 */
void draw_bar_2(t_cub3d *cub3d, t_bar draw, int x, int y)
{
	while (1)
	{
		my_pixel_put(&cub3d->map_view, x, y, get_argb(0, 255, 0, 0));
		if (x == draw.bar_x2 && y == draw.bar_y2)
			break;
		draw.e2 = 2 * draw.err;
		if (draw.e2 > -draw.dy)
		{
			draw.err -= draw.dy;
			x += draw.sx;
		}
		if (draw.e2 < draw.dx)
		{
			draw.err += draw.dx;
			y += draw.sy;
		}
	}
}

/**
 * Desenha o jogador na tela.
 *
 * Desenha o jogador na posição (x, y) na tela do jogo.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param x A coordenada x da posição do jogador.
 * @param y A coordenada y da posição do jogador.
 */
void	draw_player(t_cub3d *cub3d, int x, int y)
{
	int yy;

	yy = 1;
	y -= 3;
	while (yy <= 5)
	{
		my_pixel_put(&cub3d->map_view, x, y + yy, get_argb(0, 255, 0, 0));
		my_pixel_put(&cub3d->map_view, x - 1, y + yy, get_argb(0, 255, 0, 0));
		my_pixel_put(&cub3d->map_view, x + 1, y + yy, get_argb(0, 255, 0, 0));
		if (yy >= 2 && yy <= 4)
		{
			my_pixel_put(&cub3d->map_view, x - 2, y + yy, get_argb(0, 255, 0, 0));
			my_pixel_put(&cub3d->map_view, x + 2, y + yy, get_argb(0, 255, 0, 0));
		}
		yy++;
	}
}

/**
 * Desenha um quadrado na tela do jogo usando as coordenadas
 * fornecidas e a cor especificada.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * @param x A coordenada x do canto superior esquerdo do quadrado.
 * @param y A coordenada y do canto superior esquerdo do quadrado.
 * @param color A cor do quadrado a ser desenhado.
 */
void	draw_square(t_cub3d *cub3d, int x, int y, int color)
{
	int	x_end;
	int	y_end;
	int	y_reset;

	x_end = x + MINIMAP_SCALE;
	y_end = y + MINIMAP_SCALE;
	y_reset = y;
	while (x < x_end && x < SCREEN_WIDTH)
	{
		y = y_reset;
		while (y < y_end && y < SCREEN_HEIGHT)
		{
			my_pixel_put(&cub3d->map_view, x, y, color);
			y++;
		}
		x++;
	}
}

/**
 * Função responsável por desenhar a cena.
 * 
 * @param cub3d O ponteiro para a estrutura.
 * @param pixel_w A coordenada horizontal do pixel a ser desenhado.
 */
void draw_scene(t_cub3d *cub3d, int pixel_w)
{
	int pixel_h;
	int color;

	pixel_h = -1;
	get_tex_data(cub3d);
	while (++pixel_h < SCREEN_HEIGHT)
	{
		// desenha o ceu
		if (pixel_h < cub3d->draw.start)
		{
			color = get_argb(0, cub3d->textures.ceiling_color[0],
								cub3d->textures.ceiling_color[1], cub3d->textures.ceiling_color[2]);
			my_pixel_put(&cub3d->map_view, pixel_w, pixel_h, color);
		}
		// desenha o chao
		else if (pixel_h > cub3d->draw.end)
		{
			color = get_argb(0, cub3d->textures.floor_color[0],
								cub3d->textures.floor_color[1], cub3d->textures.floor_color[2]);
			my_pixel_put(&cub3d->map_view, pixel_w, pixel_h, color);
		}
		// desenha a parede
		else
			draw_wall(cub3d, pixel_w, pixel_h);
	}
}
