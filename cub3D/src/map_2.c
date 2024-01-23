/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:28:48 by pviegas           #+#    #+#             */
/*   Updated: 2023/09/01 12:03:21 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// coloca as imagens do jogo na janela de acordo com mapa
void	put_map(int x, int y, char c, t_game *game)
{
	int	s;

	s = 64;
	if (c == '1')
		mlx_put_image_to_window
		(game->mlx, game->win, game->img.wall, x * s, y * s);
	if (c == '0')
		mlx_put_image_to_window
		(game->mlx, game->win, game->img.floor, x * s, y * s);
	if (c == 'P')
		mlx_put_image_to_window
		(game->mlx, game->win, game->img.player, x * s, y * s);
	if (c == 'E')
		mlx_put_image_to_window
		(game->mlx, game->win, game->img.exit, x * s, y * s);
	if (c == 'C')
		mlx_put_image_to_window
		(game->mlx, game->win, game->img.collectible, x * s, y * s);
	if (c == 'O')
		mlx_put_image_to_window
		(game->mlx, game->win, game->img.on_exit, x * s, y * s);
}

// Inicializa as imagens do jogo
void	init_images(t_game *game)
{
	int	len;

	len = 64;
	game->img.wall = mlx_xpm_file_to_image(game->mlx, WALL, &len, &len);
	game->img.player = mlx_xpm_file_to_image(game->mlx, PLAYER, &len, &len);
	game->img.floor = mlx_xpm_file_to_image(game->mlx, FLOOR, &len, &len);
	game->img.exit = mlx_xpm_file_to_image(game->mlx, EXIT, &len, &len);
	game->img.collectible = mlx_xpm_file_to_image(game->mlx, BAG, &len, &len);
	game->img.on_exit = mlx_xpm_file_to_image(game->mlx, ON_EXIT, &len, &len);
}
