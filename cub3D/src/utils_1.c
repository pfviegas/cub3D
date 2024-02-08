/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:45:49 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/08 11:19:20 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * Verifica se o caractere fornecido é um espaço em branco.
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for um espaço em branco, 0 caso contrário.
 */
int	is_space(int c)
{
	if((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

/**
 * Verifica se a linha é o início do mapa.
 * 
 * Esta função verifica se a linha fornecida é o início do mapa, 
 * verificando se começa com o caractere '1' seguido de espaços em branco.
 * 
 * @param line A linha a ser verificada.
 * @return 1 se a linha for o início do mapa, 0 caso contrário.
 */
int is_start_map(char *line)
{
	int i;
	
	if (!line)
		return (0);
	i = 0;
	while(line[i] && is_space(line[i]) == 1)
		i++;
	if(line[i] != '1')
		return (0);
	else
	{	
		while(line[i] && (line[i] == '1' || line[i] == '0' || line[i] == ' ' || line[i] == '\t'))
			i++;
		if(line[i] == '\0')
			return (1);
		else
			return (0);
	}
}

/**
 * Converte uma string em um número inteiro.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 * @param str A string a ser convertida em um número inteiro.
 * @return O número inteiro convertido.
 */
int	ft_atoi_cub3d(t_cub3d *cub3d, char *str)
{
	int	res;
	int	i;

	i = 0;
	res = -1;
	(void) cub3d;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i])
	{
		if(res == -1)
			res = 0;
		if (ft_isdigit(str[i]))
			res = res * 10 + (str[i] - '0');
		else if (str[i] != '\0' && is_space(str[i]) != 1)
			return (-1);
		i++;
	}
	if (res > 255)
		return (-1);
	return (res);
}

/**
 * Imprime o mapa na saída padrão.
 *
 * @param cub3d O ponteiro para a estrutura do jogo cub3D.
 */
void	ft_print_map(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	printf("-----Mapa------\n\n");
	while(cub3d->map[i])
		printf("%s\n", cub3d->map[i++]);
	printf("\n\n");
}

/**
 * Obtém o número total de linhas no arquivo .cub.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param argv Os argumentos de linha de comando, 
 * contendo o caminho para o arquivo .cub.
 */
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
