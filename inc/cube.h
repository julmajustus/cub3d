/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:37 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/28 11:11:37 by jmakkone         ###   ########.fr       */
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

# ifndef FC_TEXTURES
#  define FC_TEXTURES 0
# endif

# ifndef ZOMBIE_COUNT
#  define ZOMBIE_COUNT 30
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
	mlx_texture_t	*succeed_screen;
	mlx_texture_t	*press_r;
	mlx_texture_t	*press_enter;
	mlx_texture_t	*press_menu_enter;
	mlx_texture_t	*exit;
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
	mlx_image_t		*kill_count;
	mlx_image_t		*highest_kill_count;
	mlx_image_t		*death_count;
}	t_window;

typedef struct s_scene
{
	int			spot_x;
	int			spot_y;
	int			y;
	int			x;
	int			offset;
	uint32_t	color;
}	t_scene;

typedef struct s_caster
{
	int				game_status;
	double			speed_multiplier;
	double			px;
	double			py;
	double			view_angle;
	double			plane_x;
	double			plane_y;
	double			view_offset;
	double			cos_table[WIDTH];
	double			sin_table[WIDTH];
	int				map_x;
	int				map_y;
	double			dist_increment_x;
	double			dist_increment_y;
	int				step_x;
	int				step_y;
	double			dist_to_grid_x;
	double			dist_to_grid_y;
	int				hit_is_horizontal[WIDTH];
	char			hit_surface[WIDTH];
	double			wall_dist[WIDTH];
	int				wall_height[WIDTH];
	int				draw_start[WIDTH];
	int				draw_end[WIDTH];
	double			wall_texture_offset_buffer[WIDTH];
	mlx_texture_t	*wall_texture;
	int				tex_x;
	int				tex_y;
	double			fc_step_x;
	double			fc_step_y;
	double			fc_base_x;
	double			fc_base_y;
	double			fc_row_dist_buffer[HEIGHT];
	double			fc_x;
	double			fc_y;
	double			cursor_pos;
	t_door			*doors;
	int				door_count;
	int				max_sprite_count;
	int				active_sprite_count;
	int				is_sprite_visible;
	t_toggle_action	*ta;
	t_sprite		**sp;
	t_sprite		*gun;
	t_spawn_point	*valid_spawn_points;
	t_window		*window;
	t_map			*map;
	t_textures		*textures;
	t_minmap		*mmap;
	int				total_spawn_points;
	int				*map_row_len_buffer;
	double			mmap_px;
	double			mmap_py;
	double			player_moved;
	double			player_rotated;
	double			elapsed_time;
	mlx_image_t		*time_text_img;
	int				blink_state;
	double			distance_to_sprite;
	struct timeval	start_time;
	struct timeval	current_time;
	double			sp_current_time;
	int				spawn_index;
	char			**av;
	char			*window_title;
	int				kill_count;
	int				highest_kill_count;
	int				death_count;
	int				*no_wall_pixel_buffer;
	int				*so_wall_pixel_buffer;
	int				*we_wall_pixel_buffer;
	int				*ea_wall_pixel_buffer;
	int				*door_pixel_buffer;
	int				*exit_pixel_buffer;
	int				*ceiling_pixel_buffer;
	int				*floor_pixel_buffer;
	int				*sp_pixel_buffer;

}	t_caster;

void	init(t_caster *c, char **av);
void	init_buffers(t_caster *c);
void	init_pixel_color_buffers(t_caster *c);
void	set_images_to_window(t_caster *c);
int		movement_up_down(t_caster *c);
int		movement_left_right(t_caster *c);
int		rotate_view_keyboard(t_caster *c);
int		rotate_view_mouse(t_caster *c);
void	keyboard_listener(mlx_key_data_t key, void *param);
void	parse_minimap(t_caster *c);
void	draw_ray(t_caster *c, int player_x, int player_y);
void	cast_rays(t_caster *c);
void	trace_ray(t_caster *c, int x);
void	render_fc_plain_colors(t_caster *c, int draw_end, int x);
void	render_fc_textures(t_caster *c, int draw_end, int x);
void	render_view(t_caster *c);
int		*get_wall_texture_buffer(t_caster *c, int x);
void	game_loop(void *param);
void	game_loop_bonus(void *param);
void	check_cursor_movement(t_caster *c);
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
void	reset_door_state(t_caster *c);
void	init_sprites(t_caster *c);
void	init_spawn_points(t_caster *c);
void	is_sprite_visible(t_caster *c, int y, int x);
void	render_sprites(t_caster *c);
void	draw_sprite(t_caster *c, t_sprite *sp, int size);
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
void	draw_text(t_caster *c, mlx_texture_t *texture, int blink);
void	draw_scene(t_caster *c, mlx_texture_t *texture, int height, int width);
int		whole_space_line(char *str);
void	draw_kill_count(t_caster *c);
void	draw_highest_kill_count(t_caster *c);
void	draw_player_death_count(t_caster *c);
void	*malloc_check(t_caster *c, void *ptr);
char	*safe_itoa(t_caster *c, int n);
char	*safe_strjoin(t_caster *c, const char *s1, const char *s2);
char	*safe_substr(t_caster *c, const char *s, \
		unsigned int start, size_t len);
char	*safe_strdup(t_caster *c, const char *s);
void	process_line(t_caster *c, char **line, int *line_check);
#endif
