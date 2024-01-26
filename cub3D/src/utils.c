/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:45:49 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/26 13:18:37 by paulo            ###   ########.fr       */
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

void	get_cub_lines(t_cub3d *cub3d, char **argv)
{
	char	*content_line;
	int		lines;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		quit("nError: Opening .cub file.", cub3d, 3);

	lines = 0;
	content_line = ft_get_next_line(fd);
	while (content_line)
	{
		free(content_line);
		lines++;
		content_line = ft_get_next_line(fd);
	}
	cub3d->cub_total_lines = lines;
	free(content_line);
	close(fd);
}

void	copy_cub(t_cub3d *cub3d, char **argv)
{
	char	*content_line;
	int		lines;
	int		fd;

	get_cub_lines(cub3d, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		quit("nError: Opening .cub file.", cub3d, 4);
	cub3d->cub = (char **)malloc(sizeof(char *) * (cub3d->cub_total_lines + 1));
	if (!cub3d->cub)
		quit("nError: Malloc error.", cub3d, 5);
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
