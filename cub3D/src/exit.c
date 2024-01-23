/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:30:09 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 12:23:45 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// imprime a mensagem de erro, liberta a memória e encerra o programa 
// de maneira controlada quando ocorrem erros ou situações excepcionais. 
void	quit(char *s, t_cub3d *cub3d, int exit_code)
{
	ft_printf("Error\n%s\n(%d)\n", s, exit_code);
	if (cub3d->map != NULL)
		free_map(cub3d);
	if (cub3d->map_floodfill != NULL)
		free_map_floodfill(cub3d);
	exit(exit_code);
}

// liberta a memória alocada para o mapa
void	free_map(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d->map)
		return ;
	i = 0;
	while (cub3d->map[i])
	{
		free(cub3d->map[i]);
		i++;
	}
	free(cub3d->map);
	cub3d->map = NULL;
}

// liberta a memória alocada para o mapa do floodfill
void	free_map_floodfill(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d->map_floodfill)
		return ;
	i = 0;
	while (cub3d->map_floodfill[i])
	{
		free(cub3d->map_floodfill[i]);
		i++;
	}
	free(cub3d->map_floodfill);
	cub3d->map_floodfill = NULL;
}

// liberta a memória alocada para as imagens e encerra o programa
int	exit_cub3d(t_cub3d *cub3d)
{
	if (cub3d->img.exit)
		mlx_destroy_image(cub3d->mlx, cub3d->img.exit);
	if (cub3d->img.collectible)
		mlx_destroy_image(cub3d->mlx, cub3d->img.collectible);
	if (cub3d->img.player)
		mlx_destroy_image(cub3d->mlx, cub3d->img.player);
	if (cub3d->img.floor)
		mlx_destroy_image(cub3d->mlx, cub3d->img.floor);
	if (cub3d->img.wall)
		mlx_destroy_image(cub3d->mlx, cub3d->img.wall);
	if (cub3d->img.on_exit)
		mlx_destroy_image(cub3d->mlx, cub3d->img.on_exit);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free_map(cub3d);
	free(cub3d->mlx);
	exit(0);
}
