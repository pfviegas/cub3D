/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:30:09 by pviegas           #+#    #+#             */
/*   Updated: 2023/09/01 12:03:29 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// imprime a mensagem de erro, liberta a memória e encerra o programa 
// de maneira controlada quando ocorrem erros ou situações excepcionais. 
void	quit(char *s, t_game *game, int exit_code)
{
	ft_printf("Error\n%s\n(%d)\n", s, exit_code);
	if (game->map != NULL)
		free_map(game);
	if (game->map_floodfill != NULL)
		free_map_floodfill(game);
	exit(exit_code);
}

// liberta a memória alocada para o mapa
void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

// liberta a memória alocada para o mapa do floodfill
void	free_map_floodfill(t_game *game)
{
	int	i;

	if (!game->map_floodfill)
		return ;
	i = 0;
	while (game->map_floodfill[i])
	{
		free(game->map_floodfill[i]);
		i++;
	}
	free(game->map_floodfill);
	game->map_floodfill = NULL;
}

// liberta a memória alocada para as imagens e encerra o programa
int	exit_game(t_game *game)
{
	if (game->img.exit)
		mlx_destroy_image(game->mlx, game->img.exit);
	if (game->img.collectible)
		mlx_destroy_image(game->mlx, game->img.collectible);
	if (game->img.player)
		mlx_destroy_image(game->mlx, game->img.player);
	if (game->img.floor)
		mlx_destroy_image(game->mlx, game->img.floor);
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.on_exit)
		mlx_destroy_image(game->mlx, game->img.on_exit);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_map(game);
	free(game->mlx);
	exit(0);
}
