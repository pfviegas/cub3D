/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:19:42 by pviegas           #+#    #+#             */
/*   Updated: 2024/02/15 17:10:05 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
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
# define M 109

// Window info
# define SCREEN_NAME "cub3D"
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define REFRESH_RATE 120

// mini map
# define MINIMAP_SCALE 8
# define MINIMAP_WIDTH 240
# define MINIMAP_HEIGHT 120

// textures
# define TEXTURE_WIDTH 320
# define TEXTURE_HEIGHT 320

// player info

# define MOVE_SPEED 3
# define BAR_LENGTH 7
# define MY_PI 3.14159265358979323846
# define MY_PI_2 1.570796327

typedef struct s_mini_map
{
	int				map_line;
	int				map_col;
	int				mini_map_line;
	int				mini_map_col;
}					t_mini_map;

typedef struct s_bar
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e2;
	int				err;
	int				bar_x2;
	int				bar_y2;
}					t_bar;

typedef struct s_tex
{
	float			wall_line_h;
	float			step;
	long long int	tex_x;
	long long int	tex_y;
	int				color;
}					t_tex;

typedef struct s_textures
{
	int				north;
	char			*north_path;
	int				south;
	char			*south_path;
	int				west;
	char			*west_path;
	int				east;
	char			*east_path;
	int				floor;
	int				floor_color[3];
	int				ceiling;
	int				ceiling_color[3];
}					t_textures;

typedef struct s_image_data
{
	void			*img;
	char			*addr;
	int				endian;
	int				bits_per_pixel;
	int				line_length;
}					t_image_data;

typedef struct s_position
{
	float			x;
	float			y;
}					t_position;

typedef struct s_step
{
	int				x;
	int				y;
}					t_step;

typedef struct s_draw
{
	int				start;
	int				end;
}					t_draw;

typedef struct s_hitbox
{
	t_position		top_left_corner;
	t_position		top_right_corner;
	t_position		bottom_left_corner;
	t_position		bottom_right_corner;
}					t_hitbox;

typedef struct s_ray
{
	t_position		ray_dir;
	t_step			step;
	t_position		delta;
	t_position		side_dist;
	int				wall_side;
	float			perp_wall_dist;
}					t_ray;

typedef struct s_move
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}					t_move;

typedef struct s_player_info
{
	void			*img;
	int				map_y;
	int				map_x;
	float			dirx;
	t_move			move;
	t_hitbox		hitbox;
	t_position		plane;
	t_position		view_dir;
	t_position		position;
}					t_player_info;

typedef struct s_cub3d
{
	void			*mlx;
	void			*win;
	t_player_info	player;
	t_ray			ray;
	t_textures		textures;
	t_image_data	north_view;
	t_image_data	south_view;
	t_image_data	west_view;
	t_image_data	east_view;
	t_image_data	map_view;
	t_draw			draw;
	t_tex			tex;
	char			**cub;
	char			**map;
	char			player_direction;
	int				start_map;
	int				cub_total_lines;
	int				map_total_lines;
	int				map_max_column;
	int				player_number;
	bool			mini_map_visible;
}					t_cub3d;

/* checks 1  */
void				map_validations(t_cub3d *cub3d);
void				check_args(t_cub3d *cub3d, int argc, char **argv);
void				check_textures(t_cub3d *cub3d);
void				check_elements(t_cub3d *cub3d, char *cl, int i);
void				check_number_elem(t_cub3d *cub3d);

/* checks 2  */
void				check_textures_images(t_cub3d *cub3d);
void				check_map(t_cub3d *cub3d);
void				check_char(t_cub3d *cub3d, char c, int line, int col);
void				check_map_surrounded_end(t_cub3d *cub3d);
void				check_map_surrounded_start(t_cub3d *cub3d);

/* checks 3  */
void				check_map_closed(t_cub3d *cub3d);
void				check_nl_middle_map(t_cub3d *cub3d);

/* cub3d  */
void				start_cub3d(t_cub3d *cub3d);
void				load_textures(t_cub3d *cub3d, t_image_data *wall,
						char *path);

/* draw 1*/
void				draw_bar(t_cub3d *cub3d, int x, int y, float angle);
void				draw_bar_2(t_cub3d *cub3d, t_bar draw, int x, int y);
void				draw_player(t_cub3d *cub3d, int x, int y);
void				draw_square(t_cub3d *cub3d, int x, int y, int color);
void				draw_scene(t_cub3d *cub3d, int pixel_w);

/* draw 2*/
void				my_pixel_put(t_image_data *img, int x, int y, int color);
void				draw_wall(t_cub3d *cub3d, int pixel_w, int pixel_h);
void				draw_mini_map(t_cub3d *cub3d, t_mini_map *mini_map);
void				draw_mini_map_border(t_cub3d *cub3d);

/* exit  */
void				quit(char *s, t_cub3d *cub3d, int exit_code);
void				free_matrix(char **str);
void				free_textures_image(t_cub3d *cub3d);
int					exit_cub3d(t_cub3d *cub3d);

/* init */
void				init_ray(t_cub3d *cub3d);
void				init_textures(t_cub3d *cub3d);
void				init_var(t_cub3d *cub3d);

/* loop hook */
int					loop_hook(t_cub3d *cub3d);
bool				check_colision(t_cub3d *cub3d, t_hitbox hitbox);
t_position			find_new_position(t_position wanted_position,
						t_position old_position, t_cub3d *cub3d);

/* map 1 */
void				get_elements_info(t_cub3d *cub3d);
void				get_map(t_cub3d *cub3d);

/* mini map */
void				render_mini_map(t_cub3d *cub3d);

/* movementes  1*/
void				move_front(t_cub3d *cub3d);
void				move_back(t_cub3d *cub3d);
void				move_right(t_cub3d *cub3d);
void				move_left(t_cub3d *cub3d);
void				update_position_player(t_cub3d *cub3d);

/* movementes  2*/
void				update_look(t_cub3d *cub3d);
void				look_left(t_cub3d *cub3d);
void				look_right(t_cub3d *cub3d);
int					key_press(int keycode, t_cub3d *cub3d);
int					key_release(int keycode, t_cub3d *cub3d);

/* player */
t_hitbox			define_hitbox(t_position player_position);
t_player_info		create_player(t_cub3d *cub3d);

/* render */
void				render_3d_view(t_cub3d *cub3d);
void				calc_step_and_side(t_cub3d *cub3d);
void				find_wall(t_cub3d *cub3d);
void				calc_wall_height(t_cub3d *cub3d);

/* utils 1*/
int					is_space(int c);
int					is_start_map(char *line);
int					atoi_cub3d(t_cub3d *cub3d, char *str);
void				ft_print_map(t_cub3d *cub3d);
void				get_cub_lines(t_cub3d *cub3d, char **argv);

/* utils 2*/
void				copy_cub(t_cub3d *cub3d, char **argv);
void				is_surrounded_1(t_cub3d *cub3d, int line, int col);
void				is_new_line(t_cub3d *cub3d, int line, int col);
void				get_colors(t_cub3d *cub3d, char *cl, int i, int flag);
void				get_textures_path(t_cub3d *cub3d, char *cl, int i,
						int flag);

/* utils 3*/
unsigned int		get_pixel_color(t_image_data *img, int x, int y);
int					get_argb(int t, int r, int g, int b);
void				get_tex_data(t_cub3d *cub3d);

#endif
