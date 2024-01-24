/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:45:49 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/24 15:47:36 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_is_space(int c)
{
	if((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_is_start_map(char *line)
{
	int	i;
	
	if (!line)
		return (0);
	i = 0;
	while(line[i] && ft_is_space(line[i]) == 1)
		i++;
	if(line[i] != '1')
		return (0);
	else
	{
		while(line[i] && (line[i] == '1' || line[i] == ' ' || line[i] == '\t'))
			i++;
//			printf("%c", line[i++]);
		// printf("PFV---%c\n",line[i]);
		if(line[i] != '\n')
			return (0);
		else
			return (1);
	}
}
int	ft_atoi_cub3d(t_cub3d *cub3d, char *str)
{
	int	res;
	int i;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		quit("Error: Format color invalid.", cub3d, 13);
		str++;
	}
	while (str[i])
	{
		if(ft_isdigit(str[i]))	
			res = res * 10 + (str[i] - '0');
		else if(str[i] != '\n')
			quit("Error: Format color.", cub3d, 14);
		i++;
	}
	if(res > 255)
		quit("Error: Format color invalid.", cub3d, 15);
	return (res);
}

void ft_print_map(t_cub3d *cub3d)
{
	int i;

	i = 0;
	printf("-----Mapa------\n\n");
	while(i <= cub3d->total_lines_map)
		printf("%s\n", cub3d->map[i++]);
}

