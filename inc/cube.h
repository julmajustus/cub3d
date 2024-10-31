/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:37 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/31 16:06:54 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "MLX42.h"
#include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

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
    NT,
    ST,
    WT,
   	ET,
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
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
}	t_textures;

typedef struct s_img
{
	mlx_t			*handle;
	mlx_image_t		*view;
	mlx_image_t		*minimap;
	mlx_image_t		*player;
}	t_img;

typedef struct s_caster
{
	char			*window_title;
	t_img			*img;
	t_map			*map;
	t_textures		*textures;
	char			**av;
	double			speed_multiplier;
	double			px;
	double			py;
	double			mmap_px;
	double			mmap_py;
	double			view_angle;
	double			plane_x;
	double			plane_y;

	double			camera;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				wall_hit_side;
	double			wall_dist;
	int				wall_height;
	int				draw_start;
	int				draw_end;
	mlx_texture_t	*wall_texture;
	int				tex_x;
	int				tex_y;
	uint32_t		pixel_color;
}	t_caster;


void	window_init(t_caster *c);
// void	read_map(t_caster *c, char **av);

int		check_collision(t_caster *c, double new_px, double new_py);
int		movement_up_down(t_caster *c);
int		movement_left_right(t_caster *c);
int		turn_left_right(t_caster *c);
void	keyboard_listener(mlx_key_data_t key, void *param);

void	parse_minimap(t_caster *c);
void	draw_player_to_minimap(t_caster *c);

void	raycaster(t_caster *c);
void	render_engine(t_caster *c);
void	game_loop(void *param);
int		check_movement(t_caster *c);
void	reset_images(t_caster *c);

void	exit_mlx(t_caster *c);
void	exit_failure(t_caster *c, char *msg);

//////////////////////////////////////////////////////
void	read_description(t_caster *c);
void	file_exist(t_caster *c, char *file, char *extension, int i);
void	check_wall(t_caster *c);
void	find_player_pos(t_caster *c);
void	check_map(t_caster *c);
void	parse_plain_colors(t_caster *c, char *line);
#endif
