/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:11:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 17:08:32 by pviegas          ###   ########.fr       */
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
	cub3d->total_header_map = 0;
	
	cub3d->map = NULL;
	cub3d->map_floodfill = NULL;
	cub3d->collectibles = 0;
	cub3d->player_x = 0;
	cub3d->player_y = 0;
	cub3d->player_on_exit = 0;
	cub3d->exit = 0;
	cub3d->player = 0;
	cub3d->column = 0;
	cub3d->end_cub3d = 0;
	cub3d->move = 1;
}

/*
// verifica se as imagens existem
static void	check_images(t_cub3d *cub3d)
{
	const char	*images[7] = {
		"./images/wall.xpm",
		"./images/player.xpm",
		"./images/floor.xpm",
		"./images/portal.xpm",
		"./images/gold-bag.xpm",
		"./images/portal1.xpm",
		"./images/portal2.xpm"
	};
	int			fd;
	int			i;

	i = 0;
	while (i <= 6)
	{
		fd = open(images[i], O_RDONLY);
		close(fd);
		if (fd == -1)
			quit("Image missing.", cub3d, 17);
		i++;
	}
}

// valida o mapa, as paredes e o caminho
static void	validations(t_cub3d *cub3d)
{
	check_map(cub3d);
	if (cub3d->column <= 0)
		quit("Invalid number of columns.", cub3d, 14);
	if (cub3d->total_lines_map <= 0)
		quit("Invalid number of lines.", cub3d, 15);
	check_walls(cub3d);
	check_path(cub3d);
}

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
	int fd_map;
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map == -1)
		quit("Fail to open map", cub3d, 3);
	get_map_info(cub3d, fd_map);
	check_number_elem(cub3d);
	
}

int	main(int argc, char **argv)
{
	t_cub3d		cub3d;
//	t_textures	textures;
	int		fd_map;

	init_var(&cub3d);
//	check_images(&cub3d);
	check_args(argc, argv);

	check_textures(&cub3d, argv);


	fd_map = open(argv[1], O_RDONLY);
	if (fd_map == -1)
	{
		write(2, "Fail to open map\n", 18);
		return(1);
	}

	cub3d.total_lines_map = get_map_lines(&cub3d, fd_map);
	close(fd_map);
/*
	fd_map = open(argv[1], O_RDONLY);
	get_map(&cub3d, fd_map);
	close(fd_map);
	validations(&cub3d);
	start_cub3d(&cub3d);
*/
	return (0);
}
