/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:35:05 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/26 13:12:41 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Função responsável por obter as informações dos elementos do mapa.
 * 
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param fd O descritor de arquivo do mapa.
 */
void get_elements_info(t_cub3d *cub3d)
{
//	char *content_line;
//	int lines;
	int i;

	i = 0;
	while(cub3d->cub[i])
	{
		printf("get_elements_info->cub3d->cub[%d] : %s\n", i, cub3d->cub[i]);
		i++;
	}
/*

	lines = 0;
	content_line = ft_get_next_line(fd);
	while (content_line && ft_is_start_map(content_line) == 0)
	{
		lines++;
		i = 0;
		while (content_line[i] && ft_is_space(content_line[i]) == 1)
			i++;
		check_elements(cub3d, content_line, i);
		free(content_line);
		content_line = ft_get_next_line(fd);
	}
	if (ft_is_start_map(content_line) == 1)
		cub3d->start_map = lines;
	free(content_line);
	if (lines == 0)
		quit("Error: file empty.", cub3d, 4);
	else if (cub3d->start_map == 0)
		quit("Error: Invalid map start.", cub3d, 5);
*/	
}





/*
// lê as linhas do mapa e retorna o número de linhas
int	get_map_lines(t_cub3d *cub3d, int fd)
{
	char	*content_line;
	int		lines;
	int	flag;

	flag = 0;
	lines = cub3d->start_map;
	content_line = ft_get_next_line(fd);
	while (content_line)
	{
		lines++;
		if (*content_line == '\n')
			flag = 1;
		if (flag == 1 && *content_line != '\n')
			flag = 2;
		free(content_line);
		content_line = ft_get_next_line(fd);
	}
	free(content_line);
	if (flag == 1)
	{
//			free(content_line);
//			ft_get_next_line(fd);
			close(fd);
			quit("Error: Invalid map.", cub3d, 16);
	}
	if (lines == cub3d->start_map)
		quit("Error: The map is empty.", cub3d, 3);
	return (lines - cub3d->start_map);
}
*/






/*


// lê as linhas do mapa e retorna o número de linhas
int	get_map_lines(t_cub3d *cub3d, int fd)
{
	char	*content_line;
	int		lines;
	int	flag;

	flag = 0;
	lines = cub3d->start_map;
	content_line = ft_get_next_line(fd);
	while (content_line)
	{
		lines++;
		if (*content_line == '\n')
			flag = 1;
		free(content_line);
		content_line = ft_get_next_line(fd);
	}
	free(content_line);
	if (flag == 1)
	{
//			free(content_line);
//			ft_get_next_line(fd);
			close(fd);
			quit("Error: Invalid map.", cub3d, 16);
	}
	if (lines == cub3d->start_map)
		quit("Error: The map is empty.", cub3d, 3);
	return (lines - cub3d->start_map);
}
*/
/*
// armazena o mapa
void	get_map(t_cub3d *cub3d, char **argv)
{
	int		i;
	int 	j;
	char	*content_line;

	i = -1;
	j = 0;
	cub3d->fd = open(argv[1], O_RDONLY);
	if (cub3d->fd == -1)
		quit("Error: Fail to open map", cub3d, 21);
	cub3d->map = (char **)malloc(sizeof(char *) * (cub3d->total_lines_map + 2));
	if (!cub3d->map)
		quit("Error: Malloc error.", cub3d, 22);
	while (++i <= cub3d->total_lines_map + cub3d->start_map )
	{
		content_line = ft_get_next_line(cub3d->fd);
		if(i >= cub3d->start_map)
			cub3d->map[j++] = ft_strtrim(content_line, "\n");
		free(content_line);
	}	
	ft_get_next_line(cub3d->fd);
	cub3d->map[j] = NULL;
	close(cub3d->fd);
}
*/

/*
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
*/
