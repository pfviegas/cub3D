/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:28:48 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/29 16:03:29 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// coloca as imagens do jogo na janela de acordo com mapa
void	put_map(int x, int y, char c, t_cub3d *cub3d)
{
	int	s;

	s = IMAGE_WIDTH;
	if (c == '1')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.wall, x * s, y * s);
	if (c == '0')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.floor, x * s, y * s);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.player, x * s, y * s);
}


// Inicializa as imagens do jogo
void	init_images(t_cub3d *cub3d)
{
	int	len;

	len = IMAGE_WIDTH;
	cub3d->img.wall = mlx_xpm_file_to_image(cub3d->mlx, WALL, &len, &len);
	cub3d->img.player = mlx_xpm_file_to_image(cub3d->mlx, PLAYER, &len, &len);
	cub3d->img.floor = mlx_xpm_file_to_image(cub3d->mlx, FLOOR, &len, &len);
}
