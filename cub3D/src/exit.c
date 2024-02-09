/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:30:09 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/09 11:27:23 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Em caso de erro exibe a mensagem de erro, encerra o programa e 
 * libera a memória alocada.
 *
 * @param s           Mensagem de erro a ser exibida.
 * @param cub3d       Ponteiro para a estrutura t_cub3d.
 * @param exit_code   Código de saída do programa.
 */
void	quit(char *s, t_cub3d *cub3d, int exit_code)
{
	printf("%s\n(%d)\n", s, exit_code);
	free_matrix(cub3d->map);
	free_matrix(cub3d->cub);
	free_textures_image(cub3d);
	exit(exit_code);
}

/**
 * Libera a memória alocada para uma matriz de strings.
 * 
 * @param str A matriz de strings a ser liberada.
 */
void	free_matrix(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

/**
 * Libera a memória alocada para as imagens das texturas.
 * 
 * @param cub3d Ponteiro para a estrutura t_cub3d.
 */
void	free_textures_image(t_cub3d *cub3d)
{
	if (cub3d->textures.north_path != NULL)
		free(cub3d->textures.north_path);
	if (cub3d->textures.south_path != NULL)
		free(cub3d->textures.south_path);
	if (cub3d->textures.west_path != NULL)
		free(cub3d->textures.west_path);
	if (cub3d->textures.east_path != NULL)
		free(cub3d->textures.east_path);
}

/**
 * Encerra o programa e libera a memória alocada.
 *
 * @param cub3d Ponteiro para a estrutura t_cub3d.
 * @return 0
 */
int	exit_cub3d(t_cub3d *cub3d)
{
	if (cub3d->north_view.img)
		mlx_destroy_image(cub3d->mlx, cub3d->north_view.img);
	if (cub3d->south_view.img)
		mlx_destroy_image(cub3d->mlx, cub3d->south_view.img);
	if (cub3d->west_view.img)
		mlx_destroy_image(cub3d->mlx, cub3d->west_view.img);
	if (cub3d->east_view.img)
		mlx_destroy_image(cub3d->mlx, cub3d->east_view.img);
	if (cub3d->map_view.img)
		mlx_destroy_image(cub3d->mlx, cub3d->map_view.img);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free_textures_image(cub3d);
	free_matrix(cub3d->cub);
	free_matrix(cub3d->map);
	free(cub3d->mlx);
	printf("Exiting CUB3D...\n");
	exit(0);
}
