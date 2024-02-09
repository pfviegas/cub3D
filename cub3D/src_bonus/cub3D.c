/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:11:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/09 15:44:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

/**
 * Inicia o ambiente gráfico.
 * 
 * Inicializa a biblioteca gráfica, cria a janela do jogo, carrega as texturas 
 * e configura os hooks de eventos do teclado e de saída. Além disso, 
 * ela inicia o loop principal do jogo.
 * 
 * @param cub3d Ponteiro para a estrutura que contém os dados.
 */
void	start_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			SCREEN_NAME);
	cub3d->map_view.img = mlx_new_image(cub3d->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	cub3d->map_view.addr = mlx_get_data_addr(cub3d->map_view.img,
			&cub3d->map_view.bits_per_pixel,
			&cub3d->map_view.line_length, &cub3d->map_view.endian);
	load_textures(cub3d, &cub3d->north_view, cub3d->textures.north_path);
	load_textures(cub3d, &cub3d->south_view, cub3d->textures.south_path);
	load_textures(cub3d, &cub3d->west_view, cub3d->textures.west_path);
	load_textures(cub3d, &cub3d->east_view, cub3d->textures.east_path);
	mlx_hook(cub3d->win, 02, 1L << 0, key_press, cub3d);
	mlx_hook(cub3d->win, 03, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->win, 17, 1L << 17, exit_cub3d, cub3d);
	mlx_loop_hook(cub3d->mlx, loop_hook, cub3d);
	mlx_loop(cub3d->mlx);
}

/**
 * Carrega as texturas do jogo.
 *
 * Carrega uma textura a partir de um arquivo de imagem no formato XPM.
 * A imagem é armazenada na estrutura t_image_data fornecida como argumento.
 *
 * @param cub3d O ponteiro para a estrutura t_cub3d.
 * @param wall O ponteiro para a estrutura t_image_data que armazenará a textura.
 * @param path O caminho para o arquivo de imagem da textura.
 */
void	load_textures(t_cub3d *cub3d, t_image_data *wall, char *path)
{
	int	tex_w;
	int	tex_h;

	tex_w = TEXTURE_WIDTH;
	tex_h = TEXTURE_HEIGHT;
	wall->img = mlx_xpm_file_to_image(cub3d->mlx, path, &tex_w, &tex_h);
	wall->addr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel,
			&wall->line_length, &wall->endian);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	init_var(&cub3d);
	check_args(&cub3d, argc, argv);
	copy_cub(&cub3d, argv);
	check_textures(&cub3d);
	get_map(&cub3d);
	map_validations(&cub3d);
	create_player(&cub3d);
	start_cub3d(&cub3d);
	exit_cub3d(&cub3d);
	return (0);
}
