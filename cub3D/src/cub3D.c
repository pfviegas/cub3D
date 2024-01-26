/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:11:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/26 20:06:18 by paulo            ###   ########.fr       */
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
	cub3d->total_lines_map = 0;
	cub3d->start_map = 0;
	cub3d->cub = NULL;
	cub3d->map = NULL;
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


/*
// valida o mapa, as paredes e o caminho
static void	validations(t_cub3d *cub3d)
{
	check_map(cub3d);
	
	// if (cub3d->col63)al_lines_map <= 0)
	// 	quit("Invalid number of lines.", cub3d, 15);
	// check_walls(cub3d);
	// check_path(cub3d);
}
*/

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

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	init_var(&cub3d);
	check_args(argc, argv);
	copy_cub(&cub3d, argv);
	check_textures(&cub3d);
	get_map(&cub3d);
	
	ft_print_map(&cub3d);
	
//	validations(&cub3d);
	
	free_matrix(cub3d.cub);
	free_textures_image(&cub3d);
	free_matrix(cub3d.map);
	//close(fd_map);
/*
	start_cub3d(&cub3d);
*/
	return (0);
}
