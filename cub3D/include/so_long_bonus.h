/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:42 by pviegas           #+#    #+#             */
/*   Updated: 2024/01/23 12:23:45 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdbool.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

// cub3d font colors
# define YELLOW 	0xF7FF00
# define RED 		0xFF0000
# define GREEN 		0x00FF00
# define BLUE 		0x0000FF
# define WHITE 		0xFFFFFF
# define BLACK 		0x000000

// images
# define WALL "./images/wall.xpm"
# define PLAYER "./images/player.xpm"
# define FLOOR "./images/floor.xpm"
# define EXIT "./images/portal.xpm"
# define BAG "./images/gold-bag.xpm"
# define ON_EXIT "./images/portal1.xpm"
# define PORTAL "./images/portal2.xpm"
# define DANGER "./images/fire.xpm"
# define DANGER1 "./images/fire_20.xpm"
# define DANGER2 "./images/fire_40.xpm"
# define DANGER3 "./images/fire_60.xpm"
# define DANGER4 "./images/fire_80.xpm"
# define DANGER5 "./images/fire_100.xpm"

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

# define ANIMATION_SPEED 50

typedef struct s_img
{
	void	*wall;
	void	*player;
	void	*floor;
	void	*exit;
	void	*collectible;
	void	*on_exit;
	void	*danger;
}	t_img;

typedef struct s_cub3d
{
	t_img	img;
	void	*mlx;
	void	*win;
	char	**map;
	char	**map_floodfill;
	char	temp;
	int		collectibles;
	int		player_cub3dy;
	int		player_x;
	int		player_y;
	int		player_on_exit ;
	int		exit;
	int		danger;
	int		player;
	int		line;
	int		column;
	int		end_cub3d;
	int		move;
	int		anim_speed;
	int		frame;
}	t_cub3d;

void		check_args(t_cub3d *cub3d, int argc, char **argv);
int			get_map_lines(t_cub3d *cub3d, int fd);
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
void		ft_print_moves(t_cub3d *cub3d);
int			animation(t_cub3d *cub3d);

#endif
