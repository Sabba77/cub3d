/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/26 11:35:50 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MOVE_SPEED 0.06
# define ROT_SPEED 0.05

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_cub
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_color;
	int		ceiling_color;
	int		has_floor;
	int		has_ceiling;
	char	**map;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_cub;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_cub		*cub;
	t_player	player;
	t_img		frame;
	t_tex		tex_no;
	t_tex		tex_so;
	t_tex		tex_we;
	t_tex		tex_ea;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	int			win_width;
	int			win_height;
}	t_mlx;

typedef struct s_map_state
{
	int	started;
	int	ended;
}	t_map_state;

int		parse_cub_file(char *path, t_cub *cub);
int		process_file_line(char *line, t_cub *cub, t_map_state *state,
			char **error);
int		parse_config_line(char *line, t_cub *cub, char **error);
int		add_map_line(t_cub *cub, char *line, char **error);
int		validate_map(t_cub *cub, char **error);
int		validate_required_data(t_cub *cub, char **error);
int		parse_color_value(char *value, int *color);
int		start_visual_test(t_cub *cub);
int		init_textures(t_mlx *mlx);
int		render_static_frame(t_cub *cub, t_mlx *mlx);
int		render_scene(t_mlx *mlx);
int		close_window(t_mlx *mlx);
int		handle_key(int keycode, t_mlx *mlx);
int		handle_key_release(int keycode, t_mlx *mlx);
int		handle_focus_out(t_mlx *mlx);
int		handle_player_input(int keycode, t_mlx *mlx);
int		handle_player_release(int keycode, t_mlx *mlx);
void	update_player_movement(t_mlx *mlx);
void	draw_ray(t_mlx *mlx, t_ray *ray, int x);
long	get_time_ms(void);
int		should_render_frame(void);
int		expose_frame(t_mlx *mlx);
int		render_loop(t_mlx *mlx);
void	put_pixel(t_img *img, int x, int y, int color);
void	destroy_textures(t_mlx *mlx);
void	destroy_visual(t_mlx *mlx);
void	init_player(t_mlx *mlx);

int		line_is_only_spaces(char *line);
int		skip_spaces(char *line, int index);
int		set_error(char **error, char *msg);
int		print_error(char *msg);

int		is_map_char(char c);
int		is_player_char(char c);
char	map_get_cell(t_cub *cub, int y, int x);

void	init_cub(t_cub *cub);
void	free_cub(t_cub *cub);

#endif
