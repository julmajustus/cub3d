/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:37 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/17 22:08:57 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# ifndef BONUS
#  define BONUS 0
# endif

# ifndef TIMEOUT
#  define TIMEOUT 120.0
# endif

# ifndef MINIMAP_SIZE
#  define MINIMAP_SIZE 200
# endif

# ifndef PLAYER_CENTER
#  define PLAYER_CENTER 100
# endif

# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE 10
# endif

# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 64
# endif
# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 64
# endif
# ifndef MAP
#  define MAP 1
# endif
# ifndef TEXTURE
#  define TEXTURE 2
# endif
# ifndef COLLISION_RADIUS
#  define COLLISION_RADIUS 0.15
# endif
# ifndef ACTION_DISTANCE
#  define ACTION_DISTANCE 1.5
# endif

typedef struct s_line
{
	char	buffer[BUFFER_SIZE];
	char	line[70000];
	int		buff_index;
	int		read_byte;
	int		line_index;
}	t_line;

typedef enum e_dir
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	end
}	t_dir;

typedef struct s_map
{
	int		map_fd;
	int		texture_fd;
	char	*map_path;
	char	*texture_path;
	int		map_width;
	int		map_height;
	char	**map_arr;
	double	scale_x;
	double	scale_y;
	double	spawn_location_x;
	double	spawn_location_y;
}	t_map;

typedef struct s_minmap
{
	int				cam_x;
	int				cam_y;
	double			ray_len;
	double			ray_angle;
	double			ray_y;
	double			ray_x;
	int				map_x;
	int				map_y;
	uint32_t		color;
	mlx_texture_t	*wall;
	mlx_texture_t	*space;
	mlx_texture_t	*door;
}	t_minmap;

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
}	t_door;

typedef struct s_spawn_point
{
	int	x;
	int	y;
}	t_spawn_point;

typedef struct s_sprite
{
	mlx_texture_t	*texture;
	double			x;
	double			y;
	int				is_visible;
	int				frame_count;
	int				death_frame_count;
	int				is_hit;
	int				current_frame;
	double			last_frame_time;
	int				frame_offset;
	int				tex_y;
	int				tex_x;
	int				tex_index;
	uint32_t		color;
	double			dx;
	double			dy;
	int				screen_y;
	int				screen_x;
	int				scale;
	double			cam_inv;
	double			cam_x;
	double			cam_y;
	double			last_spwan_time;
	int				is_animating;
	int				remaining_frames;
	double			dir_x;
	double			dir_y;
	double			dist;
	double			speed;
	int				next_tile_x;
	int				next_tile_y;
	double			dist_to_player;
}	t_sprite;

typedef struct s_toggle_action
{
	double	ray_x;
	double	ray_y;
	double	ray_step_x;
	double	ray_step_y;
	int		map_x;
	int		map_y;
}	t_toggle_action;

typedef struct s_textures
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*c_texture;
	mlx_texture_t	*f_texture;
	mlx_texture_t	*door_texture;
	mlx_texture_t	*sp_texture;
	mlx_texture_t	*menu_screen;
	mlx_texture_t	*start_screen;
	mlx_texture_t	*death_screen;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*player;
}	t_textures;

typedef struct s_window
{
	mlx_t			*handle;
	mlx_image_t		*view;
	mlx_image_t		*minimap;
	mlx_image_t		*sprite;
	mlx_image_t		*gun;
}	t_window;

typedef struct s_caster
{
	char			*window_title;
	int				game_status;
	t_window		*window;
	t_map			*map;
	t_textures		*textures;
	t_minmap		*mmap;
	char			**av;
	double			speed_multiplier;
	double			px;
	double			py;
	double			mmap_px;
	double			mmap_py;
	double			view_angle;
	double			plane_x;
	double			plane_y;
	double			view_offset;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			dist_increment_x;
	double			dist_increment_y;
	int				step_x;
	int				step_y;
	double			dist_to_grid_x;
	double			dist_to_grid_y;
	int				wall_hit_is_horizontal;
	double			wall_dist;
	int				wall_height;
	int				draw_start;
	int				draw_end;
	mlx_texture_t	*wall_texture;
	int				tex_x;
	int				tex_y;
	int				tex_index;
	uint32_t		pixel_color;
	double			cursor_pos;
	double			cos_table[WIDTH];
	double			sin_table[WIDTH];
	t_door			*doors;
	int				door_count;
	int				max_sprite_count;
	int				active_sprite_count;
	int				is_sprite_visible;
	t_toggle_action	*ta;
	t_sprite		**sp;
	t_sprite		*gun;
	t_spawn_point	*valid_spawn_points;
	int				total_spawn_points;
	double			depth_buffer[WIDTH];
	int				*map_row_len_buffer;
	double			player_moved;
	double			player_rotated;
	double			elapsed_time;
	mlx_image_t		*time_text_img;
	double			fc_row_dist;
	double			fc_row_dist_buffer[HEIGHT];
	double			fc_step_x;
	double			fc_step_y;
	double			fc_x;
	double			fc_y;
	double			fc_base_x;
	double			fc_base_y;
}	t_caster;

void	init(t_caster *c, char **av);
void	init_buffers(t_caster *c);
void	set_images_to_window(t_caster *c);
int		movement_up_down(t_caster *c);
int		movement_left_right(t_caster *c);
int		rotate_view_keyboard(t_caster *c);
int		rotate_view_mouse(t_caster *c);
void	keyboard_listener(mlx_key_data_t key, void *param);
void	parse_minimap(t_caster *c);
void	draw_player_to_minimap(t_caster *c);
void	draw_ray(t_caster *c, int player_x, int player_y);
void	raycaster(t_caster *c);
void	get_wall_texture(t_caster *c);
void	get_texture_offset(t_caster *c);
void	render_wall_column(t_caster *c, int x);
void	color_floor_and_ceiling(t_caster *c, int draw_end, int x);
void	render_floor_and_ceiling(t_caster *c, int draw_end, int x);
void	render_engine(t_caster *c);
void	game_loop(void *param);
void	check_cursor_movement(t_caster *c);
int		check_movement(t_caster *c);
int		check_collision(t_caster *c, double new_px, double new_py);
void	exit_mlx(t_caster *c);
void	exit_failure(t_caster *c, char *msg);
void	free_textures(t_caster *c);
void	read_description(t_caster *c);
void	file_exist(t_caster *c, char *file, char *extension, int i);
void	check_wall(t_caster *c);
void	find_player_pos(t_caster *c);
void	check_map(t_caster *c);
void	parse_plain_colors(t_caster *c, char *line);
void	store_door_info(t_caster *c, const char *line);
int		is_door_open(t_caster *c, int y, int x);
t_door	*find_door_in_view(t_caster *c, double max_distance);
void	toggle_door(t_caster *c, double max_distance);
void	init_sprites(t_caster *c);
void	init_spawn_points(t_caster *c);
void	is_sprite_visible(t_caster *c, int y, int x);
void	render_sprites(t_caster *c);
void	draw_sprite(t_caster *c, t_sprite *sp, \
mlx_texture_t *texture, int size);
void	get_sprite_size_and_pos(t_caster *c, \
t_sprite *sp, mlx_texture_t *texture);
void	check_sprite_hit(t_caster *c);
void	spawn_sprite(t_caster *c);
void	init_shotgun(t_caster *c);
void	render_gun(t_caster *c);
void	start_gun_fire_animation(t_sprite *gun);
void	gun_fire_animation(t_caster *c);
void	draw_player(t_caster *c);
void	put_player_in_middle(t_caster *c);
void	draw_tiles(t_caster *c, int x, int y, int flag);
void	draw_sprites(t_caster *c);
void	restrict_sizes_to_mimmap(int *x, int *y);
void	find_which_tiles(t_caster *c, int x, int y);
void	check_game_status(t_caster *c);
void	check_timeout(t_caster *c);
void	draw_elapsed_time(t_caster *c);
#endif
