/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:36:00 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 13:15:04 by pviegas          ###   ########.fr       */
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
#define CIRCLE_RADIUS 50
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

// Função para desenhar um círculo com uma barra indicando a direção
void draw_circle_with_bar(void *mlx, void *win, int x, int y, double angle) 
{
    // Desenhar o círculo
    int circle_x, circle_y;
    for (int circle_angle = 0; circle_angle <= 360; circle_angle++) {
        circle_x = x + CIRCLE_RADIUS * cos(circle_angle * M_PI / 180);
        circle_y = y + CIRCLE_RADIUS * sin(circle_angle * M_PI / 180);
        mlx_pixel_put(mlx, win, circle_x, circle_y, 0xFFFFFF);
		usleep(10000);
    }

    // Calcular as extremidades da barra com base no ângulo
    int bar_x1 = x;
    int bar_y1 = y;
    int bar_x2 = x + BAR_LENGTH * cos(angle * M_PI / 180);
    int bar_y2 = y - BAR_LENGTH * sin(angle * M_PI / 180);

    // Desenhar a linha que representa a barra
    int dx = abs(bar_x2 - bar_x1);
    int dy = abs(bar_y2 - bar_y1);
    int sx = (bar_x1 < bar_x2) ? 1 : -1;
    int sy = (bar_y1 < bar_y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx, win, bar_x1, bar_y1, 0xFFFFFF);

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

// Função para desenhar um círculo preenchido com uma barra indicadora de direção
void draw_filled_circle_with_bar(void *mlx, void *win, int x, int y, double angle) {

    // Desenhar o círculo preenchido
    for (int dx = -CIRCLE_RADIUS; dx <= CIRCLE_RADIUS; dx++) {
        for (int dy = -CIRCLE_RADIUS; dy <= CIRCLE_RADIUS; dy++) {
            int distance = sqrt(dx * dx + dy * dy);
            if (distance <= CIRCLE_RADIUS) {
                mlx_pixel_put(mlx, win, x + dx, y + dy, 0xFFFFFF); // Cor branca
            }
        }
    }

    // Calcular as extremidades da barra com base no ângulo
    int bar_x1 = x;
    int bar_y1 = y;
    int bar_x2 = x + BAR_LENGTH * cos(angle * 3.14 / 180);
    int bar_y2 = y - BAR_LENGTH * sin(angle * 3.14 / 180);

    // Desenhar a linha que representa a barra
    int dx = abs(bar_x2 - bar_x1);
    int dy = abs(bar_y2 - bar_y1);
    int sx = (bar_x1 < bar_x2) ? 1 : -1;
    int sy = (bar_y1 < bar_y2) ? 1 : -1;
    int err = dx - dy;

    while (1) 
	{
        mlx_pixel_put(mlx, win, bar_x1, bar_y1, 0xFFFFFF);

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

void rotate_360()
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_SIZE, WIN_SIZE, "Círculo Preenchido com Barra na minilibx");

    double angle = 180;

    while (angle <= 360) 
	{
		if (angle == 360)
		{
			printf("angle = 0\n");
			angle = 180;
		}
		usleep(10000);
        mlx_clear_window(mlx, win);

        // Posição central do círculo
        int center_x = WIN_SIZE / 2;
        int center_y = WIN_SIZE / 2;

        // Desenhar o círculo preenchido com a barra
        draw_filled_circle_with_bar(mlx, win, center_x, center_y, angle);


        angle++; // Aumentar o ângulo para girar a barra
    }
    mlx_loop(mlx);
}