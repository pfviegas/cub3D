/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:36:00 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 09:36:14 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/cub3D.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#define WIN_SIZE 500
#define CIRCLE_RADIUS 3
#define RED 0xFF0000

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// Função para desenhar um círculo na janela
void drawCircle(void *mlx, void *win) 
{
    int angle = 0;
	int radius = 0;
	while( radius <= CIRCLE_RADIUS)
	{
		angle = 0;
	    while (angle <= 360) 
		{
	        int x = radius * cos(angle * 3.14 / 180) + WIN_SIZE / 2;
	        int y = radius * sin(angle * 3.14 / 180) + WIN_SIZE / 2;
	        mlx_pixel_put(mlx, win, x, y, 0xFFFFFF); // Cor branca
	        angle++;
	    }
		radius++;
	}
}

// Função para desenhar uma linha horizontal
void drawHorizontalLine(void *mlx, void *win, int x1, int x2, int y, int color) {
    while (x1 <= x2)
	{
        mlx_pixel_put(mlx, win, x1, y, color);
        x1++;
    }
}

// Função para preencher um círculo na janela com uma cor específica
void fillCircle(void *mlx, void *win) 
{
    int angle = 0;
    while (angle <= 360) 
	{
        int x = CIRCLE_RADIUS * cos(angle * 3.14159265358979323846 / 180) + WIN_SIZE / 2;
        int y = CIRCLE_RADIUS * sin(angle * 3.14159265358979323846 / 180) + WIN_SIZE / 2;
//        mlx_pixel_put(mlx, win, x, y, RED); // Cor vermelha

		// Desenha uma linha horizontal centrada no ponto y do círculo
        drawHorizontalLine(mlx, win, x - CIRCLE_RADIUS, x + CIRCLE_RADIUS, y, RED);
        angle++;
    }
}

void	pixel(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_loop(mlx);
}

void	circulo(void)
{
	void	*mlx;
	void 	*win;
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_SIZE, WIN_SIZE, "Círculo na minilibx");

    // Desenhar o círculo na janela
    drawCircle(mlx, win);

    mlx_loop(mlx);
}


void circulo_filled() 
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_SIZE, WIN_SIZE, "Circulo preenchido");

    // Preencher o círculo na janela com cor vermelha
    fillCircle(mlx, win);

    mlx_loop(mlx);
}

void player() 
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_SIZE, WIN_SIZE, "Circulo preenchido");
    draw_player(mlx, win, 200, 200);
    mlx_loop(mlx);
}