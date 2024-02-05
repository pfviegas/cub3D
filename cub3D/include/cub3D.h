/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:42 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/05 11:57:16 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <math.h>
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
# define M 109

// Window info
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define SCREEN_NAME "cub3D"
# define REFRESH_RATE 120

// images
# define IMAGE_WIDTH 16
# define WALL "./images/wall.xpm"
# define FLOOR "./images/floor.xpm"
// # define PLAYER "./images/player.xpm"
// # define EXIT "./images/portal.xpm"
// # define BAG "./images/gold-bag.xpm"
// # define ON_EXIT "./images/portal1.xpm"
// # define PORTAL "./images/portal2.xpm"

// textures
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64



// player info
# define DISTANCE_MOVE 0.1 
# define ROTATION_MOVE 5
# define BAR_LENGTH 7
# define FOV 0.66

typedef struct s_tex {
	float	wall_line_h;
	float	step;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_tex;

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
	int floor_color[3];
	int	ceiling;
	int ceiling_color[3];
}	t_textures;

typedef struct	s_image_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image_data;

typedef struct s_img
{
	void		*wall;
	void		*floor;
}	t_img;


typedef struct s_position {
	float	x;
	float	y;
}	t_position;

typedef struct s_step {
	int	x;
	int	y;
}	t_step;

typedef struct s_draw{
	int	start;
	int	end;
}	t_draw;

typedef struct s_hitbox {
	t_position	top_left_corner;
	t_position	top_right_corner;
	t_position	bottom_left_corner;
	t_position	bottom_right_corner;
}	t_hitbox;

typedef struct s_ray {
	t_position	ray_dir;
	t_step		step;
	t_position	delta;
	t_position	side_dist;
	int			wall_side;
	float		prep_wall_dist;
}	t_ray;

typedef struct s_player_info {
	t_position	position;
	t_hitbox	hitbox;
	void		*img;
	float		dirx;
	t_position	view_dir;
	t_position	plane;
	int			map_x;
	int			map_y;
}	t_player_info;

typedef struct s_cub3d
{
	void			*mlx;
	void			*win;
	t_player_info	player;
	t_ray			ray;
	t_img			img;
	t_textures		textures;
	t_image_data	north_view;
	t_image_data	south_view;
	t_image_data	west_view;
	t_image_data	east_view;
	t_image_data	map_view;
	t_draw			draw;
//	t_image_data	scene;
	char			**cub;
	int				cub_total_lines;
	char		**map;
	int			map_total_lines;
	int			map_max_column;
	char		player_direction;
	double		angle_direction;
	int			collectibles;
	int			player_cub3dy;
	// float	player_xx;
	// float	player_yy;
	int			player_on_exit ;
	int			exit;
	int			player_number;
	int			start_map;
	int			end_cub3d;
	int			move;
	bool		mini_map_visible;
	t_tex		tex;
}	t_cub3d;

void		check_args(t_cub3d *cub3d, int argc, char **argv);
void		get_cub_lines(t_cub3d *cub3d, char **argv);
void		copy_cub(t_cub3d *cub3d, char **argv);
void		check_textures(t_cub3d *cub3d);
void		get_elements_info(t_cub3d *cub3d);
void		check_textures_images(t_cub3d *cub3d);

void		get_map(t_cub3d *cub3d);
void		check_nl_middle_map(t_cub3d *cub3d);
void		map_validations(t_cub3d *cub3d);
void		is_surrounded_1(t_cub3d *cub3d, int line, int col);
void		is_new_line(t_cub3d *cub3d, int line, int col);


int			is_space(int c);
int			is_start_map(char *line);
void		check_elements(t_cub3d *cub3d, char *cl, int i);
void		check_number_elem(t_cub3d *cub3d);
int			ft_atoi_cub3d(t_cub3d *cub3d, char *str);
void		ft_print_map(t_cub3d *cub3d);
void		is_surrounded_1(t_cub3d *cub3d, int line, int col);
void 		free_matrix(char **str);


void		check_map(t_cub3d *cub3d);
void		check_char(t_cub3d *cub3d, char c, int line, int col);
void		quit(char *s, t_cub3d *cub3d, int exit_code);
void		check_map_closed(t_cub3d *cub3d);
int			exit_cub3d(t_cub3d *cub3d);
void		free_textures_image(t_cub3d *cub3d);
void		start_cub3d(t_cub3d *cub3d);
int			key_handling(int keycode, t_cub3d *cub3d);
void		init_images(t_cub3d *cub3d);
int			render_mini_map(t_cub3d *cub3d);
void		put_map(int x, int y, char c, t_cub3d *cub3d);


void draw_player(void *mlx, void *win, int x, int y);
void rotate_360();
void draw_circle_with_bar(void *mlx, void *win, int x, int y, double angle);
void draw_bar(t_cub3d *cub3d, int x, int y);

void	check_map_surrounded_end(t_cub3d *cub3d);
void	check_map_surrounded_start(t_cub3d *cub3d);
void	ft_print_map_char(char **str);
void	load_textures(t_cub3d *cub3d, t_image_data *wall, char *path);
void	render_3d_view(t_cub3d *cub3d);
void	calc_step_and_side(t_cub3d *cub3d);
t_player_info   create_player(t_cub3d *cub3d);
void	find_wall(t_cub3d *cub3d);
void	calc_wall_height(t_cub3d *cub3d);
void	get_tex_data(t_cub3d *cub3d);
void	draw_scene(t_cub3d *cub3d, int pixel_w);
void	my_pixel_put(t_image_data *img, int x, int y, int color);
void	draw_wall(t_cub3d *cub3d, int pixel_w, int pixel_h);
unsigned int	get_color(t_image_data *img, int x, int y);
int	create_trgb(int t, int r, int g, int b);

int	loop_hook(t_cub3d *cub3d);
#endif
