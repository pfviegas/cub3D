/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:35:11 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/31 09:38:51 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	put_map(int x, int y, char c, t_cub3d *cub3d)
{
	int	s;

	s = IMAGE_WIDTH;
	if (c == '1')
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.wall, x * s, y * s);
	//if (c == '0')
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
	{
		mlx_put_image_to_window
		(cub3d->mlx, cub3d->win, cub3d->img.floor, x * s, y * s);
    //	draw_player(cub3d->mlx, cub3d->win, cub3d->player_x * 16 + 8, cub3d->player_y * 16 + 4);
	}
		
		//mlx_put_image_to_window
		//(cub3d->mlx, cub3d->win, cub3d->img.player, x * s, y * s);
}


// Inicializa as imagens do jogo
void	init_images(t_cub3d *cub3d)
{
	int	len;

	len = IMAGE_WIDTH;
	cub3d->img.wall = mlx_xpm_file_to_image(cub3d->mlx, WALL, &len, &len);
	//cub3d->img.player = mlx_xpm_file_to_image(cub3d->mlx, PLAYER, &len, &len);
	cub3d->img.floor = mlx_xpm_file_to_image(cub3d->mlx, FLOOR, &len, &len);
}
