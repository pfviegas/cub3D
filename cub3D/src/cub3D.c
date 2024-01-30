/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:11:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/30 11:43:09 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// inicializa as variáveis do cub3D
static void	init_var(t_cub3d *cub3d)
{
	cub3d->textures.north = 0;
	cub3d->textures.south = 0;
	cub3d->textures.east = 0;
	cub3d->textures.west = 0;
	cub3d->textures.floor = 0;
	cub3d->textures.ceiling = 0;
	cub3d->map_total_lines = 0;
	cub3d->start_map = 0;
	cub3d->cub = NULL;
	cub3d->map = NULL;
	cub3d->map_max_column = 0;
	cub3d->map_floodfill = NULL;
	cub3d->textures.north_path = NULL;
	cub3d->textures.south_path = NULL;
	cub3d->textures.west_path = NULL;
	cub3d->textures.east_path = NULL;
	cub3d->player_x = 0;
	cub3d->player_y = 0;
	cub3d->player = 0;
	cub3d->player_direction = '9';
	
	cub3d->end_cub3d = 0;
	cub3d->move = 1;
}


// inicializa o ambiente gráfico, as imagens e o jogo
void	start_cub3d(t_cub3d *cub3d)
{
	t_image_data	img;
//	int				offset;
	
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->map_max_column * IMAGE_WIDTH,
			cub3d->map_total_lines * IMAGE_WIDTH, "cub3D");
	init_images(cub3d);
	render_map(cub3d);
// colocar o player no mapa (pixels)
	img.img = mlx_new_image(cub3d->mlx, 16, 16);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
//	offset = (y * line_length + x * (bits_per_pixel / 8));
	mlx_hook(cub3d->win, 02, 1L << 0, key_handling, cub3d);
	mlx_hook(cub3d->win, 17, 1L << 17, exit_cub3d, cub3d);
	mlx_loop(cub3d->mlx);
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
	
	ft_print_map(&cub3d);	
//	ft_print_map_flood(&cub3d);	

	printf("total lines: %d\n", cub3d.map_total_lines);
	printf("cub3d->player : %d\n", cub3d.player);
	printf("cub3d->player_y (line): %d\n", cub3d.player_y);
	printf("cub3d->player_x (col): %d\n", cub3d.player_x);
	printf("cub3d->player_direction : %c\n\n", cub3d.player_direction);

	start_cub3d(&cub3d);

	quit("", &cub3d, 0);
	return (0);
}
