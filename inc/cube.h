/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:37 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/08 17:43:11 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include <MLX42/MLX42.h>
// # include "MLX42.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# ifndef BONUS
#  define BONUS 0
# endif
# define MINIMAP_WIDTH 200  // 미니맵 너비
# define MINIMAP_HEIGHT 200 // 미니맵 높이
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

typedef struct s_line
{
    char buffer[BUFFER_SIZE];
    char line[70000];
    int buff_index;
    int read_byte;
    int line_index;
} t_line;

typedef enum 
{
    NO,
    SO,
    WE,
   	EA,
	F,
	C,
	end
} T_Dir;

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
}	t_map;

typedef struct s_textures
{
	mlx_texture_t *north_texture;
	mlx_texture_t *south_texture;
	mlx_texture_t *west_texture;
	mlx_texture_t *east_texture;
	uint32_t ceiling_color;
	uint32_t floor_color;
	mlx_texture_t *mmap_wall;
	mlx_texture_t *mmap_space;
	mlx_texture_t *player;

} t_textures;

typedef struct s_window
{
	mlx_t *handle;
	mlx_image_t *view;
	mlx_image_t *minimap;
} t_window;

typedef struct s_caster
{
	char *window_title;
	t_window *window;
	t_map *map;
	t_textures *textures;
	char **av;
	double speed_multiplier;
	double px;
	double py;
	double mmap_px;
	double mmap_py;
	double view_angle;
	double plane_x;
	double plane_y;

	double view_offset;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double dist_increment_x;
	double dist_increment_y;
	int step_x;
	int step_y;
	double dist_to_grid_x;
	double dist_to_grid_y;
	int wall_hit_is_horizontal;
	double wall_dist;
	int wall_height;
	int draw_start;
	int draw_end;
	mlx_texture_t *wall_texture;
	int tex_x;
	int tex_y;
	uint32_t pixel_color;
	double cursor_pos;
	double	cos_table[WIDTH];
	double	sin_table[WIDTH];
} t_caster;

void init(t_caster *c, char **av);
void set_images_to_window(t_caster *c);
// void read_map(t_caster *c, char **av);

int movement_up_down(t_caster *c);
int movement_left_right(t_caster *c);
int rotate_view_keyboard(t_caster *c);
int rotate_view_mouse(t_caster *c);
void keyboard_listener(mlx_key_data_t key, void *param);

void parse_minimap(t_caster *c);
void draw_player_to_minimap(t_caster *c);

void raycaster(t_caster *c);
void render_engine(t_caster *c);
void game_loop(void *param);
void check_cursor_movement(t_caster *c);
int check_movement(t_caster *c);
int	check_collision(t_caster *c, double new_px, double new_py);

void exit_mlx(t_caster *c);
void exit_failure(t_caster *c, char *msg);
//////////////////////////////////////////////////////
void	read_description(t_caster *c);
void	file_exist(t_caster *c, char *file, char *extension, int i);
void	check_wall(t_caster *c);
void	find_player_pos(t_caster *c);
void	check_map(t_caster *c);
void	parse_plain_colors(t_caster *c, char *line);
// void	update_minimap(t_caster *c);

#endif
