/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:35:05 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 17:22:43 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// lê as linhas do mapa e verifica se a informacao das texturas estao correctas
void	get_map_info(t_cub3d *cub3d, int fd)
{
	char	*content_line;
	int		lines;
	int		i;

	lines = 0;
	content_line = ft_get_next_line(fd);
	while (content_line && ft_is_start_map(content_line) == 0)
	{
		lines++;
		i = 0;
		while(content_line[i] && ft_is_space(content_line[i]) == 1)
			i++;
		check_elements(cub3d, content_line, i);
		free(content_line);
		content_line = ft_get_next_line(fd);
	}
	if (ft_is_start_map(content_line) == 1)
		cub3d->total_header_map = lines;
	printf("cub3d->total_header_map: %d\n", cub3d->total_header_map);
	free(content_line);
	if (lines == 0)
		quit("The file is empty.", cub3d, 3);
	else if (cub3d->total_header_map == 0)
		quit("Invalid map start.", cub3d, 4);
}

// lê as linhas do mapa e retorna o número de linhas
int	get_map_lines(t_cub3d *cub3d, int fd)
{
	char	*content_line;
	int		lines;

	lines = cub3d->total_header_map;
	content_line = ft_get_next_line(fd);
	while (content_line)
	{
		lines++;
		if (*content_line == '\n')
		{
			free(content_line);
			quit("Invalid map.", cub3d, 16);
		}
		free(content_line);
		content_line = ft_get_next_line(fd);
	}
	if (lines == cub3d->total_header_map)
		quit("The map is empty.", cub3d, 3);
	free(content_line);
	return (lines - cub3d->total_header_map);
}

// armazena o mapa e o número de colunas
void	get_map(t_cub3d *cub3d, int fd)
{
	int		i;
	char	*content_line;

	i = 0;
	cub3d->map = (char **)malloc(sizeof(char *) * (cub3d->total_lines_map + 1));
	cub3d->map_floodfill = (char **)malloc(sizeof(char *) * (cub3d->total_lines_map + 1));
	if (!cub3d->map || !cub3d->map_floodfill)
		quit("Malloc error.", cub3d, 4);
	while (i < cub3d->total_lines_map)
	{
		content_line = ft_get_next_line(fd);
		cub3d->map[i] = ft_strtrim(content_line, "\n");
		cub3d->map_floodfill[i] = ft_strtrim(content_line, "\n");
		free(content_line);
		i++;
	}
	ft_get_next_line(fd);
	cub3d->map[i] = NULL;
	cub3d->map_floodfill[i] = NULL;
	cub3d->column = ft_strlen(cub3d->map[i - 1]);
}

// renderiza o mapa
int	render_map(t_cub3d *cub3d)
{
	int	y;
	int	x;
	int	s;

	s = 64;
	if (cub3d->collectibles == 0)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->img.exit);
//		cub3d->img.exit = mlx_xpm_file_to_image(cub3d->mlx, PORTAL, &s, &s);
	}
	y = 0;
	while (y < cub3d->total_lines_map)
	{
		x = 0;
		while (x < cub3d->column)
		{
			put_map(x, y, cub3d->map[y][x], cub3d);
			x++;
		}
		y++;
	}
	return (0);
}
