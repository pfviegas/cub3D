/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:37:40 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/02/06 16:38:44 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Renderiza a visão 3D do jogo.
 *
 * @param cub3d Ponteiro para a estrutura que contém os dados.
 * 
 * camera_x = posição x da câmera na tela.
 * -1 lado esquerdo da tela
 * 0 centro da tela
 * 1 lado direito da tela
 * 
 * ray_dir.x = direção x do raio
 * ray.delta.x = distância entre os raios
 * player.view_dir.x = direção x da visão do jogador
 * player.plane.x = direção x do plano da câmera
 * player.map_x = coordenada x do mapa
 */
void render_3d_view(t_cub3d *cub3d)
{
	float camera_x;
	int pixel_w;

	pixel_w = -1;
	while (++pixel_w < SCREEN_WIDTH)
	{
		camera_x = 2 * pixel_w / (float)(SCREEN_WIDTH) - 1;
		cub3d->ray.ray_dir.x = cub3d->player.view_dir.x + cub3d->player.plane.x * camera_x;
		cub3d->ray.ray_dir.y = cub3d->player.view_dir.y + cub3d->player.plane.y * camera_x;
		cub3d->player.map_x = (int)cub3d->player.position.x;
		cub3d->player.map_y = (int)cub3d->player.position.y;
		cub3d->ray.delta.x = sqrt(1 + pow(cub3d->ray.ray_dir.y, 2) / pow(cub3d->ray.ray_dir.x, 2));
		cub3d->ray.delta.y = sqrt(1 + pow(cub3d->ray.ray_dir.x, 2) / pow(cub3d->ray.ray_dir.y, 2));
		calc_step_and_side(cub3d);
		find_wall(cub3d);
		calc_wall_height(cub3d);
		draw_scene(cub3d, pixel_w);
	}
}

/**
 * Função responsável por calcular os passos e as distâncias laterais do raio.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * 
 * cub3d->ray.step.x = passo a dar pelo player 
 * 						(-1 move-se para a esquerda do eixo x)
 *						(1 move-se para a direita do eixo x)
 * cub3d->ray.step.y = passo a dar pelo player 
 * 						(-1 move-se para a esquerda do eixo y)
 *						(1 move-se para a direita do eixo y)
 * ray.side_dist.x = distância lateral x
 * ray.side_dist.y = distância lateral y
 */
void calc_step_and_side(t_cub3d *cub3d)
{
	if (cub3d->ray.ray_dir.x < 0)
	{
		cub3d->ray.step.x = -1;
		cub3d->ray.side_dist.x = (cub3d->player.position.x - (int)cub3d->player.position.x) * cub3d->ray.delta.x;
	}
	else
	{
		cub3d->ray.step.x = 1;
		cub3d->ray.side_dist.x = ((int)cub3d->player.position.x + 1 - cub3d->player.position.x) * cub3d->ray.delta.x;
	}
	if (cub3d->ray.ray_dir.y < 0)
	{
		cub3d->ray.step.y = -1;
		cub3d->ray.side_dist.y = (cub3d->player.position.y - (int)cub3d->player.position.y) * cub3d->ray.delta.y;
	}
	else
	{
		cub3d->ray.step.y = 1;
		cub3d->ray.side_dist.y = ((int)cub3d->player.position.y + 1 - cub3d->player.position.y) * cub3d->ray.delta.y;
	}
}

/**
 * Função responsável por encontrar a parede em que o raio colide.
 * DDA Algorithm
 * 
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * wall_side = 0 -> horizontal (x)
 * wall_side = 1 -> vertical (y)
 */
void find_wall(t_cub3d *cub3d)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub3d->ray.side_dist.x < cub3d->ray.side_dist.y)
		{
			cub3d->ray.side_dist.x += cub3d->ray.delta.x;
			cub3d->player.map_x += cub3d->ray.step.x;
			cub3d->ray.wall_side = 0;
		}
		else
		{
			cub3d->ray.side_dist.y += cub3d->ray.delta.y;
			cub3d->player.map_y += cub3d->ray.step.y;
			cub3d->ray.wall_side = 1;
		}
		if (cub3d->map[cub3d->player.map_y][cub3d->player.map_x] == '1')
			hit = 1;
	}
}

/**
 * Calcula a altura da parede.
 * 
 * Calcula a altura da parede com base na distância preparada
 * e define os valores de início e fim para desenhar a parede na tela.
 * 
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 */
void calc_wall_height(t_cub3d *cub3d)
{
	cub3d->tex.wall_line_h = 0;
	if (cub3d->ray.wall_side == 0)
		cub3d->ray.perp_wall_dist = fabs((cub3d->player.map_x
					- cub3d->player.position.x + (1 - cub3d->ray.step.x) / 2)
				/ cub3d->ray.ray_dir.x);
	else
		cub3d->ray.perp_wall_dist = fabs((cub3d->player.map_y
					- cub3d->player.position.y + (1 - cub3d->ray.step.y) / 2)
				/ cub3d->ray.ray_dir.y);
	cub3d->tex.wall_line_h = (int)(SCREEN_HEIGHT / cub3d->ray.perp_wall_dist);
	cub3d->draw.start = -cub3d->tex.wall_line_h / 2 + SCREEN_HEIGHT / 2;
	if (cub3d->draw.start < 0)
		cub3d->draw.start = 0;
	cub3d->draw.end = cub3d->tex.wall_line_h / 2 + SCREEN_HEIGHT / 2;
	if (cub3d->draw.end >= SCREEN_HEIGHT)
		cub3d->draw.end = SCREEN_HEIGHT - 1;
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
	// if (cub3d->mini_map_visible == true)
	// 	render_mini_map(cub3d);
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
 * A expressão `(float)TEXTURE_HEIGHT / cub3d->tex.wall_line_h` calcula 
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
void get_tex_data(t_cub3d *cub3d)
{
	float wall_x;

	cub3d->tex.tex_x = 0;
	cub3d->tex.tex_y = 0;
	if (cub3d->ray.wall_side == 0)
		wall_x = cub3d->player.position.y + cub3d->ray.perp_wall_dist * cub3d->ray.ray_dir.y;
	else
		wall_x = cub3d->player.position.x + cub3d->ray.perp_wall_dist * cub3d->ray.ray_dir.x;

	wall_x -= floor(wall_x);
	cub3d->tex.tex_x = wall_x * TEXTURE_WIDTH;
	cub3d->tex.step = (float)TEXTURE_HEIGHT / cub3d->tex.wall_line_h;
}

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
void draw_wall(t_cub3d *cub3d, int pixel_w, int pixel_h)
{
	cub3d->tex.tex_y = (int)(((float)pixel_h - (float)SCREEN_HEIGHT / 2.0 + (float)cub3d->tex.wall_line_h / 2.0) * cub3d->tex.step);

	if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x > 0)
		cub3d->tex.color = get_color(&cub3d->east_view, cub3d->tex.tex_x, cub3d->tex.tex_y);
	else if (cub3d->ray.wall_side == 0 && cub3d->ray.ray_dir.x < 0)
		cub3d->tex.color = get_color(&cub3d->west_view, cub3d->tex.tex_x, cub3d->tex.tex_y);
	else if (cub3d->ray.wall_side == 1 && cub3d->ray.ray_dir.y > 0)
		cub3d->tex.color = get_color(&cub3d->south_view, cub3d->tex.tex_x, cub3d->tex.tex_y);
	else
		cub3d->tex.color = get_color(&cub3d->north_view, cub3d->tex.tex_x, cub3d->tex.tex_y);

	my_pixel_put(&cub3d->map_view, pixel_w, pixel_h, cub3d->tex.color);
}

/**
 * Obtém a cor de um pixel específico em uma imagem.
 *
 * @param img A estrutura de dados da imagem.
 * @param x A coordenada x do pixel.
 * @param y A coordenada y do pixel.
 * @return A cor do pixel.
 */
unsigned int	get_color(t_image_data *img, int x, int y)
{
	char *dst;
	unsigned int color;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return color;
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
