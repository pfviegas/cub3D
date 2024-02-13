/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:58:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/13 17:57:47 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Verifica se o mapa está fechado.
 * 
 * Verifica se o mapa fornecido está fechado, ou seja, se todas as bordas
 * do mapa são compostas por caracteres '1'. Caso contrário, a função 
 * encerra o programa exibindo uma mensagem de erro.
 * 
 * @param cub3d - A estrutura principal do jogo cub3D.
 */
void	check_map_closed(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j] && cub3d->map[i][j] == ' ')
			j++;
		if (cub3d->map[i][j] != '1')
			quit("Error:\n Invalid map line start.", cub3d, 32);
		i++;
	}
	i = 0;
	while (cub3d->map[i])
	{
		j = ft_strlen(cub3d->map[i]) - 1;
		while (j > 0 && cub3d->map[i][j] == ' ')
			j--;
		if (cub3d->map[i][j] != '1')
			quit("Error:\n Invalid map line end.", cub3d, 33);
		i++;
	}
}

/**
 * Verifica se há uma linha vazia no meio do mapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	check_nl_middle_map(t_cub3d *cub3d)
{
	int	lines;
	int	flag;

	flag = 0;
	lines = cub3d->start_map;
	while (cub3d->cub[lines])
	{
		if (flag == 0 && cub3d->cub[lines][0] == '\0')
			flag = 1;
		if (flag == 1 && cub3d->cub[lines][0] != '\0')
			flag = 2;
		lines++;
	}
	if (flag == 2)
	{
		quit("Error:\n Mapa inválido.", cub3d, 19);
	}
	if (lines == cub3d->start_map)
		quit("Error:\n O mapa está vazio.", cub3d, 20);
	else if (lines == cub3d->start_map + 1)
		quit("Error:\n Mapa inválido.", cub3d, 21);
}
