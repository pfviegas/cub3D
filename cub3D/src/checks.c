/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:02 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/31 09:32:21 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// valida o mapa, as paredes e o caminho
void	map_validations(t_cub3d *cub3d)
{
	check_map(cub3d);
	
	if (cub3d->map_total_lines <= 2)
		quit("nError: Invalid number of lines.", cub3d, 27);
	 check_map_closed(cub3d);
}

// verifica se o programa foi chamado com o número correto de argumentos 
// e se o argumento fornecido tem a extensão .ber. 
void	check_args(t_cub3d *cub3d, int argc, char **argv)
{
	if (argc != 2)
		quit("nError: Invalid number of argument.\n", cub3d, 1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		quit("nError: File must be of type .cub\n", cub3d, 2);
}

void	check_textures(t_cub3d *cub3d)
{
	get_elements_info(cub3d);
	check_number_elem(cub3d);
	check_textures_images(cub3d);
}

void	get_textures_path(t_cub3d *cub3d, char *cl, int i, int flag)
{
	while(cl[i] && is_space(cl[i]) == 1)
		i++;
	if(flag == 1)
	{
		cub3d->textures.north++;
		cub3d->textures.north_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
	if(flag == 2)
	{
		cub3d->textures.south++;
		cub3d->textures.south_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
	if(flag == 3)
	{
		cub3d->textures.west++;
		cub3d->textures.west_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
	if(flag == 4)
	{
		cub3d->textures.east++;
		cub3d->textures.east_path = ft_substr(cl, i, ft_strlen(cl) - i);
	}
}

void	get_colors_path(t_cub3d *cub3d, char *cl, int i, int flag)
{
	char	*temp;
	char	**temp_array;
	int j;

	j = -1;
	temp = ft_substr(cl, i, ft_strlen(cl) - i);
	temp_array = ft_split(temp,',');
	while(temp_array[++j])
	{
		if((flag == 5 || flag == 6) && ft_atoi_cub3d(cub3d, temp_array[j]) < 0)
			return (free_matrix(temp_array), free(temp), \
					quit("nError: Format color invalid.", cub3d, 30));
		else if (flag == 6)
			cub3d->textures.ceiling_color[j] = ft_atoi_cub3d(cub3d, temp_array[j]);
		else if (flag == 5)
			cub3d->textures.floor_color[j] = ft_atoi_cub3d(cub3d, temp_array[j]);
	}
	free_matrix(temp_array);
	free(temp);
	if (j != 3)
		quit("nError: Format color invalid (RGB).", cub3d, 31);
	if(flag == 5)
		cub3d->textures.floor++;
	if(flag == 6)
		cub3d->textures.ceiling++;
}

void	check_elements(t_cub3d *cub3d, char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
		get_textures_path(cub3d, str, i + 2, 1);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		get_textures_path(cub3d, str, i + 2, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		get_textures_path(cub3d, str, i + 2, 3);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		get_textures_path(cub3d, str, i + 2, 4);
	else if (str[i] == 'F')
		get_colors_path(cub3d, str, i + 1, 5);
	else if (str[i] == 'C')
		get_colors_path(cub3d, str, i + 1, 6);
	else if(str[i] != '\0' )
		quit("nError: Invalid element line.", cub3d, 29);
}

void	check_number_elem(t_cub3d *cub3d)
{
	if (cub3d->textures.north != 1)
		quit("nError: Invalid element line.", cub3d, 9);
	if (cub3d->textures.south != 1)
		quit("nError: Invalid element line.", cub3d, 10);
	if (cub3d->textures.west != 1)
		quit("nError: Invalid element line.", cub3d, 11);
	if (cub3d->textures.east != 1)
		quit("nError: Invalid element line.", cub3d, 12);
	if (cub3d->textures.floor != 1)
		quit("nError: Invalid element line.", cub3d, 13);
	if (cub3d->textures.ceiling != 1)
		quit("nError: Invalid element line.", cub3d, 14);
}

// verifica se as imagens existem
void	check_textures_images(t_cub3d *cub3d)
{
	int fd;

	fd = open(cub3d->textures.north_path, O_RDONLY);
	if (fd == -1)
		quit("nError: North image missing.", cub3d, 15);
	close(fd);
	fd = open(cub3d->textures.south_path, O_RDONLY);
	if (fd == -1)
		quit("nError: South image missing.", cub3d, 16);
	close(fd);
	fd = open(cub3d->textures.west_path, O_RDONLY);
	if (fd == -1)
		quit("nError: West image missing.", cub3d, 17);
	close(fd);
	fd = open(cub3d->textures.east_path, O_RDONLY);
	if (fd == -1)
		quit("nError: East image missing.", cub3d, 18);
	close(fd);
}

// verifica se o mapa tem apenas os caracteres permitidos.
void	check_map(t_cub3d *cub3d)
{
	int	line;
	int	col;

	line = 0;
	while (cub3d->map[line] != NULL)
	{
		col = 0;
		while (cub3d->map[line][col] == ' ')
			col++;
		while (cub3d->map[line][col])
		{
			check_char(cub3d, cub3d->map[line][col], line, col);
			col++;
		}
		if (cub3d->map_max_column < col)
			cub3d->map_max_column = col;
		line++;
	}
	if (cub3d->player == 0)
		quit("nError: There's no player.", cub3d, 25);
	else if (cub3d->player > 1)
		quit("nError: Just one player per map.", cub3d, 26);
}

// verifica se o caractere é válido e se for espaco valida os caracteres adjacentes.
void	check_char(t_cub3d *cub3d, char c, int line, int col)
{
	if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		cub3d->player++;
		cub3d->player_y = line;
		cub3d->player_x = col;
		cub3d->player_yy = line;
		cub3d->player_xx = col + 0.15;
		cub3d->player_direction = c;
	}
	else if (c == '0' || c == '1')
		return ;
	else if (c == ' ')
		is_surrounded_1(cub3d, line, col);
	else
		quit("nError: Invalid characters.", cub3d, 23);
}

// verifica se o mapa esta fechado por paredes
void	check_map_closed(t_cub3d *cub3d)
{
	if (floodfill(cub3d) == 0)
	{
		quit("Invalid path on the map", cub3d, 13);
	}
}
