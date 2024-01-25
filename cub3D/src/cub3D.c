/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:11:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/25 12:36:46 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
// inicializa as variáveis do jogo
static void	init_var(t_cub3d *cub3d)
{
	cub3d->textures.north = 0;
	cub3d->textures.south = 0;
	cub3d->textures.east = 0;
	cub3d->textures.west = 0;
	cub3d->textures.floor = 0;
	cub3d->textures.ceiling = 0;
	cub3d->total_lines_map = 0;
	cub3d->start_map = 0;
	cub3d->map = NULL;
	cub3d->fd = 9999;
	cub3d->textures.north_path = NULL;
	cub3d->textures.south_path = NULL;
	cub3d->textures.west_path = NULL;
	cub3d->textures.east_path = NULL;
	cub3d->player_x = 0;
	cub3d->player_y = 0;
	cub3d->player = 0;
	
	//cub3d->player_direction = 0;
	cub3d->column = 0;
	cub3d->end_cub3d = 0;
	cub3d->move = 1;
}

// verifica se as imagens existem
static void	check_textures_images(t_cub3d *cub3d)
{
	cub3d->fd = open(cub3d->textures.north_path, O_RDONLY);
	if (cub3d->fd == -1)
		quit("Error: North image missing.", cub3d, 17);
	else
		close(cub3d->fd);
	cub3d->fd = open(cub3d->textures.south_path, O_RDONLY);
	if (cub3d->fd == -1)
		quit("Error: South image missing.", cub3d, 18);
	else
		close(cub3d->fd);
	cub3d->fd = open(cub3d->textures.west_path, O_RDONLY);
	if (cub3d->fd == -1)
		quit("Error: West image missing.", cub3d, 19);
	else
		close(cub3d->fd);
	cub3d->fd = open(cub3d->textures.east_path, O_RDONLY);
	if (cub3d->fd == -1)
		quit("Error: East image missing.", cub3d, 20);
	else
		close(cub3d->fd);
	cub3d->fd = 9999;
}

// valida o mapa, as paredes e o caminho
static void	validations(t_cub3d *cub3d)
{
	check_map(cub3d);
	
	// if (cub3d->column <= 0)
	// 	quit("Invalid number of columns.", cub3d, 14);
	// if (cub3d->total_lines_map <= 0)
	// 	quit("Invalid number of lines.", cub3d, 15);
	// check_walls(cub3d);
	// check_path(cub3d);
}

/*
// inicializa o ambiente gráfico, as imagens e o jogo
void	start_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->column * 64,
			cub3d->total_lines_map * 64, "So_long");
	init_images(cub3d);
	render_map(cub3d);
	mlx_hook(cub3d->win, 02, 1L << 0, key_handling, cub3d);
	mlx_hook(cub3d->win, 17, 1L << 17, exit_cub3d, cub3d);
	mlx_loop(cub3d->mlx);
}
*/

void	check_textures(t_cub3d *cub3d, char **argv)
{
	cub3d->fd = open(argv[1], O_RDONLY);
	if (cub3d->fd == -1)
		quit("Error: Fail to open map", cub3d, 3);
	get_elements_info(cub3d, cub3d->fd);
	check_number_elem(cub3d);
	cub3d->total_lines_map = get_map_lines(cub3d, cub3d->fd);
	close(cub3d->fd);
}

int	main(int argc, char **argv)
{
	t_cub3d		cub3d;
//	t_textures	textures;

	init_var(&cub3d);
	check_args(argc, argv);
	check_textures(&cub3d, argv);
	check_textures_images(&cub3d);
	get_map(&cub3d, argv);
	
	printf("cub3d.start_map = %d\n", cub3d.start_map);
	printf("cub3d->total_lines_map = %d\n", cub3d.total_lines_map);
	ft_print_map(&cub3d);
	validations(&cub3d);
	

	
	free_textures_image(&cub3d);
	free_map(&cub3d);
	//close(fd_map);
/*
	start_cub3d(&cub3d);
*/
	return (0);
}
