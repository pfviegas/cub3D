/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:02 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/26 15:55:54 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// verifica se o programa foi chamado com o número correto de argumentos 
// e se o argumento fornecido tem a extensão .ber. 
void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error: Invalid number of argument.\n", 36);
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		write(2, "Error: File must be of type .cub\n", 34);
		exit(2);
	}
}

void	check_textures(t_cub3d *cub3d)
{
	get_elements_info(cub3d);
	check_number_elem(cub3d);
	check_textures_images(cub3d);
}

void	get_textures_path(t_cub3d *cub3d, char *cl, int i, int flag)
{
	while(cl[i] && ft_is_space(cl[i]) == 1)
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

	j = 0;	
	temp = ft_substr(cl, i, ft_strlen(cl) - i);
	temp_array = ft_split(temp,',');
	while(temp_array[j])
	{
		if(flag == 5)
			cub3d->textures.floor_color[j] = ft_atoi_cub3d(cub3d, temp_array[j]);
		if(flag == 6)
			cub3d->textures.ceiling_color[j] = ft_atoi_cub3d(cub3d, temp_array[j]);
		j++;
		if (j > 3)
			quit("Error: Format color invalid.", cub3d, 12);
	}
	if(flag == 5)
		cub3d->textures.floor++;
	if(flag == 6)
		cub3d->textures.ceiling++;
	while (j >= 0)
		free(temp_array[j--]);
	free(temp_array);
	free(temp);
}

void	check_elements(t_cub3d *cub3d, char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O' && ft_is_space(str[i + 2]) == 1)
		get_textures_path(cub3d, str, i + 2, 1);
	else if (str[i] == 'S' && str[i + 1] == 'O'  && ft_is_space(str[i + 2]) == 1)
		get_textures_path(cub3d, str, i + 2, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E'  && ft_is_space(str[i + 2]) == 1)
		get_textures_path(cub3d, str, i + 2, 3);
	else if (str[i] == 'E' && str[i + 1] == 'A'  && ft_is_space(str[i + 2]) == 1)
		get_textures_path(cub3d, str, i + 2, 4);
	else if (str[i] == 'F' && ft_is_space(str[i + 1]) == 1)
		get_colors_path(cub3d, str, i + 2, 5);
	else if (str[i] == 'C' && ft_is_space(str[i + 1]) == 1)
		get_colors_path(cub3d, str, i + 2, 6);
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
		col = -1;
		while (cub3d->map[line][++col])
			check_char(cub3d, cub3d->map[line][col], line, col);
		line++;
	}
	if (cub3d->player == 0)
		quit("Error: There's no player.", cub3d, 24);
	else if (cub3d->player > 1)
		quit("Error: Just one player per map.", cub3d, 25);
}

// Função para verificar se uma coordenada está rodeada de 1s
void	is_surrounded_1(t_cub3d *cub3d, int line, int col)
{
	int	i;
	int j;
	
	i = line - 1;
	while (i <= line + 1)
	{
		j = col - 1;
		while (j <= col + 1)
		{
			if (i >= 0 && i <= cub3d->total_lines_map \
				&& j >= 0 && j < (int)ft_strlen(cub3d->map[i]))
				if (cub3d->map[i][j] != '1')
					if (cub3d->map[i][j] != ' ')
						quit("Error: Invalid map.", cub3d, 26);
			j++;
		}
		i++;
	}
}

// Função para verificar se uma coordenada está rodeada de 1s
void	is_new_line(t_cub3d *cub3d, int line, int col)
{
	int	i;
	int j;
	
	i = line - 1;
	while (i <= line + 1)
	{
		j = col - 1;
		while (j <= col + 1)
		{
			if (i >= 0 && i <= cub3d->total_lines_map \
				&& j >= 0 && j < (int)ft_strlen(cub3d->map[i]))
				if (cub3d->map[i][j] != '1')
					if (cub3d->map[i][j] != ' ')
						quit("Error: Invalid map.", cub3d, 26);
			j++;
		}
		i++;
	}
}

void	check_char(t_cub3d *cub3d, char c, int line, int col)
{
	if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		cub3d->player++;
		cub3d->player_y = col;
		cub3d->player_x = line;
		cub3d->player_direction = c;
	}
	else if (c == '1' || c == '0')
		return ;
	else if (c == ' ')
		is_surrounded_1(cub3d, line, col);
	else
		quit("Error: Invalid characters.", cub3d, 23);

//	printf("cub3d->player : %d\n", cub3d->player);
//	printf("cub3d->player_x : %d\n", cub3d->player_x);
//	printf("cub3d->player_y : %d\n", cub3d->player_y);
//	printf("cub3d->player_direction : %c\n", cub3d->player_direction);
}

// verifica se o mapa está cercado por paredes.
void	check_walls(t_cub3d *cub3d)
{
	int	line;
	int	col;

	line = 0;
	while (cub3d->map[line])
	{
		col = 0;
		while (cub3d->map[line][col])
		{
			if (cub3d->map[0][col] != '1' ||
				cub3d->map[cub3d->total_lines_map - 1][col] != '1')
				quit("The map is not surrounded by walls", cub3d, 12);
			if (cub3d->map[line][0] != '1' ||
				cub3d->map[line][cub3d->column - 1] != '1')
				quit("The map is not surrounded by walls", cub3d, 12);
			col++;
		}
		line++;
	}
}
/*
// verifica se o caminho do jogador é válido.
void	check_path(t_cub3d *cub3d)
{
	if (!floodfill(cub3d))
	{
		quit("Invalid path on the map", cub3d, 13);
	}
}
*/
