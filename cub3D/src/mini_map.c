/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:37:45 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/14 13:25:11 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Define a linha do minimapa com base na posição do jogador.
 *
 * Calcula a linha do minimapa com base na posição atual do jogador.
 * Se a posição y do jogador for maior que a metade da altura do minimapa 
 * dividida pela escala do minimapa, a linha do minimapa será definida como 0. 
 * Caso contrário, a linha do minimapa será calculada como o valor absoluto da 
 * diferença entre a posição y do jogador e a metade da altura do minimapa 
 * dividida pela escala do minimapa, subtraído de 1.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param mini_map O ponteiro para a estrutura t_mini_map.
 */
void	set_mini_map_line(t_cub3d *cub3d, t_mini_map *mini_map)
{
	if (((int)cub3d->player.position.y > \
		(int)((MINIMAP_HEIGHT / 2) / MINIMAP_SCALE)))
		mini_map->mini_map_line = 0;
	else
		mini_map->mini_map_line = abs((int)(cub3d->player.position.y - \
		((MINIMAP_HEIGHT / 2) / MINIMAP_SCALE)) - 1);
}

/**
 * Define a coluna do minimapa com base na posição do jogador.
 *
 * Calcula a coluna do minimapa com base na posição atual do jogador.
 * Se a posição x do jogador for maior que a metade da largura do minimapa 
 * dividida pela escala do minimapa, a coluna do minimapa será definida como 0.
 * Caso contrário, a coluna do minimapa será calculada como o valor absoluto 
 * da diferença entre a posição x do jogador e a metade da largura do minimapa
 * dividida pela escala do minimapa, subtraído por 1.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param mini_map O ponteiro para a estrutura t_mini_map.
 */
void	set_mini_map_col(t_cub3d *cub3d, t_mini_map *mini_map)
{
	if (((int)cub3d->player.position.x > \
		(int)((MINIMAP_WIDTH / 2) / MINIMAP_SCALE)))
		mini_map->mini_map_col = 0;
	else
		mini_map->mini_map_col = abs((int)(cub3d->player.position.x - \
		((MINIMAP_WIDTH / 2) / MINIMAP_SCALE)) - 1);
}

/**
 * Define o valor da variável "line" com base na posição do jogador.
 * "line" representa a coordenada y da posição do jogador no minimapa.
 *
 * @param cub3d O ponteiro para a estrutura cub3d.
 * @param line  O ponteiro para a variável "line" a ser definida.
 */
void	set_line(t_cub3d *cub3d, int *line)
{
	*line = (int)(cub3d->player.position.y - \
		(MINIMAP_HEIGHT / (MINIMAP_SCALE * 2)) - 1);
	if (*line < 0)
		*line = -1;
}

/**
 * Cria o mini mapa com base nas estruturas cub3d e mini_map fornecidas.
 * 
 * @param cub3d A estrutura principal cub3d.
 * @param mini_map A estrutura mini_map.
 */
void	create_mini_map(t_cub3d *cub3d, t_mini_map *mini_map)
{
	int		line;
	int		col;

	set_line(cub3d, &line);
	while (cub3d->map[++line] && \
		(mini_map->mini_map_line * MINIMAP_SCALE) < MINIMAP_HEIGHT)
	{
		set_mini_map_col(cub3d, mini_map);
		col = (int)(cub3d->player.position.x - \
			(MINIMAP_WIDTH / (MINIMAP_SCALE * 2)) - 1);
		if (col < 0)
			col = -1;
		while (cub3d->map[line][++col] && \
			(mini_map->mini_map_col * MINIMAP_SCALE) < MINIMAP_WIDTH)
		{
			if (col <= (int)ft_strlen(cub3d->map[line]))
			{
				mini_map->map_line = line;
				mini_map->map_col = col;
				draw_mini_map(cub3d, mini_map);
			}
			mini_map->mini_map_col++;
		}
		mini_map->mini_map_line++;
	}
}

/**
 * Renderiza o minimapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 */
void	render_mini_map(t_cub3d *cub3d)
{
	t_mini_map	mini_map;

	set_mini_map_line(cub3d, &mini_map);
	create_mini_map(cub3d, &mini_map);
	draw_mini_map_border(cub3d);
	draw_player(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2));
	draw_bar(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2), (-0.5));
	draw_bar(cub3d, ((MINIMAP_WIDTH / 2) + 3), (MINIMAP_HEIGHT / 2), (0.5));
}
