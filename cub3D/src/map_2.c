/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:28:48 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/26 13:13:29 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// coloca as imagens do jogo na janela de acordo com mapa
void	put_map(int x, int y, char c, t_cub3d *cub3d)
{
	int	s;

	s = 64;
	if (c == '1')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.wall, x * s, y * s);
	if (c == '0')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.floor, x * s, y * s);
	if (c == 'P')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.player, x * s, y * s);
	if (c == 'E')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.exit, x * s, y * s);
	if (c == 'C')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.collectible, x * s, y * s);
	if (c == 'O')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.on_exit, x * s, y * s);
}

/*
// Inicializa as imagens do jogo
void	init_images(t_cub3d *cub3d)
{
	int	len;

	len = 64;
//	cub3d->img.wall = mlx_xpm_file_to_image(cub3d->mlx, WALL, &len, &len);
//	cub3d->img.player = mlx_xpm_file_to_image(cub3d->mlx, PLAYER, &len, &len);
//	cub3d->img.floor = mlx_xpm_file_to_image(cub3d->mlx, FLOOR, &len, &len);
//	cub3d->img.exit = mlx_xpm_file_to_image(cub3d->mlx, EXIT, &len, &len);
//	cub3d->img.collectible = mlx_xpm_file_to_image(cub3d->mlx, BAG, &len, &len);
//	cub3d->img.on_exit = mlx_xpm_file_to_image(cub3d->mlx, ON_EXIT, &len, &len);
}
*/
