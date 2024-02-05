/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:11:04 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/05 15:22:58 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_ray(t_cub3d *cub3d)
{
	cub3d->ray.delta.x = 0;
	cub3d->ray.delta.y = 0;
	cub3d->ray.ray_dir.x = 0;
	cub3d->ray.ray_dir.y = 0;
	cub3d->ray.side_dist.x = 0;
	cub3d->ray.side_dist.y = 0;
	cub3d->ray.step.x = 0;
	cub3d->ray.step.y = 0;
	cub3d->ray.wall_side = 0;
	cub3d->ray.perp_wall_dist = 0;
	cub3d->draw.start = 0;
	cub3d->draw.end = 0;
	
}
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
	cub3d->textures.north_path = NULL;
	cub3d->textures.south_path = NULL;
	cub3d->textures.west_path = NULL;
	cub3d->textures.east_path = NULL;
	cub3d->player.position.x = 0;
	cub3d->player.position.y = 0;
	cub3d->player_number = 0;
	cub3d->player_direction = '9';
	cub3d->angle_direction = 0;
	cub3d->mini_map_visible = false;

	cub3d->end_cub3d = 0;
	cub3d->move = 1;
	
	init_ray(cub3d);
	
}


// inicializa o ambiente gráfico, as imagens e o jogo
void	start_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
	init_images(cub3d);
	 if (cub3d->mini_map_visible == true)
	 	render_mini_map(cub3d);
	cub3d->map_view.img = mlx_new_image(cub3d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub3d->map_view.addr = mlx_get_data_addr(cub3d->map_view.img, &cub3d->map_view.bits_per_pixel,
			&cub3d->map_view.line_length, &cub3d->map_view.endian);


	load_textures(cub3d, &cub3d->north_view, cub3d->textures.north_path);
	load_textures(cub3d, &cub3d->south_view, cub3d->textures.south_path);
	load_textures(cub3d, &cub3d->west_view, cub3d->textures.west_path);
	load_textures(cub3d, &cub3d->east_view, cub3d->textures.east_path);

	
	mlx_hook(cub3d->win, 02, 1L << 0, key_handling, cub3d);
	mlx_hook(cub3d->win, 17, 1L << 17, exit_cub3d, cub3d);
	mlx_loop_hook(cub3d->mlx, loop_hook, cub3d);	
	mlx_loop(cub3d->mlx);
}

void	load_textures(t_cub3d *cub3d, t_image_data *wall, char *path)
{
	int	tex_w;
	int	tex_h;

	tex_w = IMAGE_WIDTH;
	tex_h = IMAGE_WIDTH;
	wall->img = mlx_xpm_file_to_image(cub3d->mlx, path, &tex_w, &tex_h);
	wall->addr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel, &wall->line_length,
			&wall->endian);
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
	
//	ft_print_map(&cub3d);	
//	ft_print_map_flood(&cub3d);	

	// printf("total lines: %d\n", cub3d.map_total_lines);
	// printf("cub3d->player : %d\n", cub3d.player);
	// printf("cub3d->player_y (line): %d\n", cub3d.player_y);
	// printf("cub3d->player_x (col): %d\n", cub3d.player_x);
	// printf("cub3d->player_direction : %c\n\n", cub3d.player_direction);

	start_cub3d(&cub3d);

	quit("", &cub3d, 0);
	return (0);
}
