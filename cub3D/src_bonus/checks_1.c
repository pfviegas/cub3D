/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:02 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/13 17:57:47 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/**
 * Realiza as validações do mapa.
 *
 * Esta função realiza uma série de validações no mapa do jogo cub3D.
 * As validações incluem verificar se o mapa é válido, se possui um número
 * mínimo de linhas, se está fechado corretamente, se o ponto de partida
 * está cercado e se o ponto de saída está cercado.
 *
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 */
void	map_validations(t_cub3d *cub3d)
{
	check_map(cub3d);
	if (cub3d->map_total_lines <= 2)
		quit("Error:\n Invalid number of lines.", cub3d, 27);
	check_map_closed(cub3d);
	check_map_surrounded_start(cub3d);
	check_map_surrounded_end(cub3d);
}

/**
 * Verifica os argumentos passados para o programa.
 *
 * @param cub3d - O ponteiro para a estrutura de dados 'cub3d'.
 * @param argc - Número de argumentos passados para o programa.
 * @param argv - Array de strings contendo os argumentos passados.
 */
void	check_args(t_cub3d *cub3d, int argc, char **argv)
{
	if (argc != 2)
		quit("Error:\n Número inválido de argumentos.\n", cub3d, 1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		quit("Error:\n O arquivo deve ser do tipo .cub\n", cub3d, 2);
}

/**
 * Verifica as texturas do jogo.
 * 
 * Esta função chama outras funções para obter informações 
 * sobre os elementos do jogo, verificar se o número de elementos 
 * está correto e verificar se as imagens das texturas estão corretas.
 * 
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 */
void	check_textures(t_cub3d *cub3d)
{
	get_elements_info(cub3d);
	check_number_elem(cub3d);
	check_textures_images(cub3d);
}

/**
 * Verifica os elementos presentes em uma linha do arquivo de configuração.
 * 
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 * @param str A string contendo a linha do arquivo de configuração.
 * @param i O índice inicial da verificação na string.
 */
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
		get_colors(cub3d, str, i + 1, 5);
	else if (str[i] == 'C')
		get_colors(cub3d, str, i + 1, 6);
	else if (str[i] != '\0')
		quit("Error:\n Linha de elemento inválida.", cub3d, 29);
}

/**
 * Verifica se o número de elementos necessários foi corretamente definido.
 * 
 * @param cub3d O ponteiro para a estrutura de dados 'cub3d'.
 */
void	check_number_elem(t_cub3d *cub3d)
{
	if (cub3d->textures.north != 1)
		quit("Error:\n Linha de elemento inválida.", cub3d, 9);
	if (cub3d->textures.south != 1)
		quit("Error:\n Linha de elemento inválida.", cub3d, 10);
	if (cub3d->textures.west != 1)
		quit("Error:\n Linha de elemento inválida.", cub3d, 11);
	if (cub3d->textures.east != 1)
		quit("Error:\n Linha de elemento inválida.", cub3d, 12);
	if (cub3d->textures.floor != 1)
		quit("Error:\n Linha de elemento inválida.", cub3d, 13);
	if (cub3d->textures.ceiling != 1)
		quit("Error:\n Linha de elemento inválida.", cub3d, 14);
}
