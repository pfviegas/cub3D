/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:42 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/24 10:56:50 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

// keycodes
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define ARROW_LEFT 65361
# define ARROW_UP 65362
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364

typedef struct s_textures
{
	int	north;
	char *north_path;
	int	south;
	char *south_path;
	int	west;
	char *west_path;
	int	east;
	char *east_path;
	int	floor;
	char *floor_path;
	int	ceiling;
	char *ceiling_path;
}	t_textures;

typedef struct s_img
{
	void	*wall;
	void	*player;
	void	*floor;
	void	*exit;
	void	*collectible;
	void	*on_exit;
}	t_img;

typedef struct s_cub3d
{
	t_img		img;
	t_textures	textures;
	void		*mlx;
	void		*win;
	char		**map;
	char		**map_floodfill;
	char		temp;
	int			collectibles;
	int			player_cub3dy;
	int			player_x;
	int			player_y;
	int			player_on_exit ;
	int			exit;
	int			player;
	int			total_header_map;
	int			total_lines_map;
	int			column;
	int			end_cub3d;
	int			move;
}	t_cub3d;

void		check_args(int argc, char **argv);
int			get_map_lines(t_cub3d *cub3d, int fd);
void		get_map_info(t_cub3d *cub3d, int fd);
int			ft_is_space(int c);
int			ft_is_start_map(char *line);
void		check_elements(t_cub3d *cub3d, char *cl, int i);
void		check_number_elem(t_cub3d *cub3d);

void		get_map(t_cub3d *cub3d, int fd);
void		check_map(t_cub3d *cub3d);
void		check_char(t_cub3d *cub3d, char c, int line, int col);
void		quit(char *s, t_cub3d *cub3d, int exit_code);
void		check_walls(t_cub3d *cub3d);
void		check_path(t_cub3d *cub3d);
int			floodfill(t_cub3d *cub3d);
bool		fill(t_cub3d *cub3d, char c, int line, int col);
int			exit_cub3d(t_cub3d *cub3d);
void		free_map(t_cub3d *cub3d);
void		free_map_floodfill(t_cub3d *cub3d);
void		start_cub3d(t_cub3d *cub3d);
int			key_handling(int keycode, t_cub3d *cub3d);
void		init_images(t_cub3d *cub3d);
int			render_map(t_cub3d *cub3d);
void		put_map(int x, int y, char c, t_cub3d *cub3d);

#endif
