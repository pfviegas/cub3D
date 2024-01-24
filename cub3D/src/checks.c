/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:02 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/24 17:05:13 by pveiga-c         ###   ########.fr       */
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
void	get_textures_path(t_cub3d *cub3d, char *cl, int i, int flag)
{
	while(cl[i] && ft_is_space(cl[i]) == 1)
		i++;
	if(flag == 1)
	{
		cub3d->textures.north++;
		cub3d->textures.north_path = ft_substr(cl, i, ft_strlen(cl) - i - 1);
	}
	if(flag == 2)
	{
		cub3d->textures.south++;
		cub3d->textures.south_path = ft_substr(cl, i, ft_strlen(cl) - i - 1);
	}
	if(flag == 3)
	{
		cub3d->textures.west++;
		cub3d->textures.west_path = ft_substr(cl, i, ft_strlen(cl) - i - 1);
	}
	if(flag == 4)
	{
		cub3d->textures.east++;
		cub3d->textures.east_path = ft_substr(cl, i, ft_strlen(cl) - i - 1);
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

void	check_elements(t_cub3d *cub3d, char *cl, int i)
{
	if (cl[i] == 'N' && cl[i + 1] == 'O' && ft_is_space(cl[i + 2]) == 1)
		get_textures_path(cub3d, cl, i + 2, 1);
	else if (cl[i] == 'S' && cl[i + 1] == 'O'  && ft_is_space(cl[i + 2]) == 1)
		get_textures_path(cub3d, cl, i + 2, 2);
	else if (cl[i] == 'W' && cl[i + 1] == 'E'  && ft_is_space(cl[i + 2]) == 1)
		get_textures_path(cub3d, cl, i + 2, 3);
	else if (cl[i] == 'E' && cl[i + 1] == 'A'  && ft_is_space(cl[i + 2]) == 1)
		get_textures_path(cub3d, cl, i + 2, 4);
	else if (cl[i] == 'F' && ft_is_space(cl[i + 1]) == 1)
		get_colors_path(cub3d, cl, i + 2, 5);
	else if (cl[i] == 'C' && ft_is_space(cl[i + 1]) == 1)
		get_colors_path(cub3d, cl, i + 2, 6);
}

void	check_number_elem(t_cub3d *cub3d)
{
	if (cub3d->textures.north != 1)
		quit("Error: Invalid element line.", cub3d, 6);
	if (cub3d->textures.south != 1)
		quit("Error: Invalid element line.", cub3d, 7);
	if (cub3d->textures.west != 1)
		quit("Error: Invalid element line.", cub3d, 8);
	if (cub3d->textures.east != 1)
		quit("Error: Invalid element line.", cub3d, 9);
	if (cub3d->textures.floor != 1)
		quit("Error: Invalid element line.", cub3d, 10);
	if (cub3d->textures.ceiling != 1)
		quit("Error: Invalid element line.", cub3d, 11);
}




// verifica se o mapa do jogo cumpre com as condições necessárias.
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
	// else if (c == ' ')
	// 	ft_check_spaces(cub3d, c, line, col);
	else
		quit("Error: Invalid characters.", cub3d, 23);
	printf("cub3d->player : %d\n", cub3d->player);
	printf("cub3d->player_x : %d\n", cub3d->player_x);
	printf("cub3d->player_y : %d\n", cub3d->player_y);
	printf("cub3d->player_direction : %c\n", cub3d->player_direction);
	
}

// void	ft_check_spaces(t_cub3d *cub3d, char c, int line, int col)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while()
// }

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

// verifica se o caminho do jogador é válido.
void	check_path(t_cub3d *cub3d)
{
	if (!floodfill(cub3d))
	{
		quit("Invalid path on the map", cub3d, 13);
	}
}
