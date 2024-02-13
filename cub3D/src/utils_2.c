/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:45:49 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/13 17:57:47 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Copia o conteúdo do arquivo .cub para a estrutura de dados do cub3D.
 * 
 * @param cub3d A estrutura de dados do cub3D.
 * @param argv Os argumentos de linha de comando, 
 * onde argv[1] é o caminho para o arquivo .cub.
 */
void	copy_cub(t_cub3d *cub3d, char **argv)
{
	char	*content_line;
	int		lines;
	int		fd;

	get_cub_lines(cub3d, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		quit("Error:\n Opening .cub file.", cub3d, 4);
	cub3d->cub = (char **)malloc(sizeof(char *) * (cub3d->cub_total_lines + 1));
	if (!cub3d->cub)
		quit("Error:\n Malloc error.", cub3d, 5);
	lines = 0;
	content_line = ft_get_next_line(fd);
	while (content_line)
	{
		cub3d->cub[lines] = ft_strtrim(content_line, "\n");
		free(content_line);
		lines++;
		content_line = ft_get_next_line(fd);
	}
	cub3d->cub[lines] = NULL;
	free(content_line);
	ft_get_next_line(fd);
	close(fd);
}

/**
 * Verifica se a posição (line, col) está cercada por paredes.
 * 
 * @param cub3d O ponteiro para a estrutura de dados do cub3D.
 * @param line A linha da posição a ser verificada.
 * @param col A coluna da posição a ser verificada.
 */
void	is_surrounded_1(t_cub3d *cub3d, int line, int col)
{
	int	i;
	int	j;

	if (line == 0)
		i = line;
	else
		i = line - 1;
	while (cub3d->map[i] && i <= line + 1)
	{
		if (col == 0)
			j = col;
		else
			j = col - 1;
		while (j <= col + 1)
		{
			if (i <= cub3d->map_total_lines \
				&& j < (int)ft_strlen(cub3d->map[i]))
				if (cub3d->map[i][j] != '1')
					if (cub3d->map[i][j] != ' ')
						quit("Error:\n Invalid map.", cub3d, 24);
			j++;
		}
		i++;
	}
}

/**
 * Verifica se a posição atual é uma nova linha válida no mapa.
 * 
 * @param cub3d O ponteiro para a estrutura de dados do cub3D.
 * @param line A linha atual no mapa.
 * @param col A coluna atual no mapa.
 */
void	is_new_line(t_cub3d *cub3d, int line, int col)
{
	int	i;
	int	j;

	i = line - 1;
	while (i <= line + 1)
	{
		j = col - 1;
		while (j <= col + 1)
		{
			if (i >= 0 && i <= cub3d->map_total_lines \
				&& j >= 0 && j < (int)ft_strlen(cub3d->map[i]))
			{
				if (cub3d->map[i][j] != '1')
				{
					if (cub3d->map[i][j] != ' ')
					{
						quit("Error:\n Invalid map.", cub3d, 38);
					}
				}
			}
			j++;
		}
		i++;
	}
}

/**
 * Função responsável por obter as cores e verificar as cores.
 * 
 * @param cub3d O ponteiro para a estrutura de dados do cub3D.
 * @param cl String contendo a linha do arquivo .cub que contém as cores.
 * @param i Índice de início da substring contendo as cores.
 * @param flag Flag indicando se as cores são do chão (5) ou do teto (6).
 */
void	get_colors(t_cub3d *cub3d, char *cl, int i, int flag)
{
	char	*temp;
	char	**temp_array;
	int		j;

	j = -1;
	temp = ft_substr(cl, i, ft_strlen(cl) - i);
	temp_array = ft_split(temp, ',');
	while (temp_array[++j])
	{
		if ((flag == 5 || flag == 6) && atoi_cub3d(cub3d, temp_array[j]) < 0)
			return (free_matrix(temp_array), free(temp), \
					quit("Error:\n Formato de cor inválido.", cub3d, 30));
		else if (flag == 6)
			cub3d->textures.ceiling_color[j] = atoi_cub3d(cub3d, temp_array[j]);
		else if (flag == 5)
			cub3d->textures.floor_color[j] = atoi_cub3d(cub3d, temp_array[j]);
	}
	free_matrix(temp_array);
	free(temp);
	if (j != 3)
		quit("Error:\n Formato de cor inválido (RGB).", cub3d, 31);
	if (flag == 5)
		cub3d->textures.floor++;
	if (flag == 6)
		cub3d->textures.ceiling++;
}

/**
 * Função responsável por obter o caminho das texturas do jogo.
 * 
 * @param cub3d O ponteiro para a estrutura de dados do cub3D.
 * @param cl String contendo a linha do arquivo de configuração.
 * @param i Índice inicial da string cl.
 * @param flag Flag indicando qual textura está sendo processada.
 */
void	get_textures_path(t_cub3d *cub3d, char *cl, int i, int flag)
{
	while (cl[i] && is_space(cl[i]) == 1)
		i++;
	if (flag == 1)
	{
		cub3d->textures.north++;
		cub3d->textures.north_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
	if (flag == 2)
	{
		cub3d->textures.south++;
		cub3d->textures.south_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
	if (flag == 3)
	{
		cub3d->textures.west++;
		cub3d->textures.west_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
	if (flag == 4)
	{
		cub3d->textures.east++;
		cub3d->textures.east_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
}
