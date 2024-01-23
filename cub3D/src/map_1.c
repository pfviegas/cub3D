/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:35:05 by pviegas           #+#    #+#             */
/*   Updated: 2023/09/01 12:03:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// lê as linhas do mapa e retorna o número de linhas
int	get_lines(t_game *game, int fd)
{
	char	*content_line;
	int		lines;

	lines = 0;
	content_line = ft_get_next_line(fd);
	while (content_line)
	{
		lines++;
		if (*content_line == '\n')
		{
			free(content_line);
			quit("Invalid map.", game, 16);
		}
		free(content_line);
		content_line = ft_get_next_line(fd);
	}
	if (lines == 0)
		quit("The file is empty or not exist.", game, 3);
	free(content_line);
	return (lines);
}

// armazena o mapa e o número de colunas
void	get_map(t_game *game, int fd)
{
	int		i;
	char	*content_line;

	i = 0;
	game->map = (char **)malloc(sizeof(char *) * (game->line + 1));
	game->map_floodfill = (char **)malloc(sizeof(char *) * (game->line + 1));
	if (!game->map || !game->map_floodfill)
		quit("Malloc error.", game, 4);
	while (i < game->line)
	{
		content_line = ft_get_next_line(fd);
		game->map[i] = ft_strtrim(content_line, "\n");
		game->map_floodfill[i] = ft_strtrim(content_line, "\n");
		free(content_line);
		i++;
	}
	ft_get_next_line(fd);
	game->map[i] = NULL;
	game->map_floodfill[i] = NULL;
	game->column = ft_strlen(game->map[i - 1]);
}

// renderiza o mapa
int	render_map(t_game *game)
{
	int	y;
	int	x;
	int	s;

	s = 64;
	if (game->collectibles == 0)
	{
		mlx_destroy_image(game->mlx, game->img.exit);
		game->img.exit = mlx_xpm_file_to_image(game->mlx, PORTAL, &s, &s);
	}
	y = 0;
	while (y < game->line)
	{
		x = 0;
		while (x < game->column)
		{
			put_map(x, y, game->map[y][x], game);
			x++;
		}
		y++;
	}
	return (0);
}
