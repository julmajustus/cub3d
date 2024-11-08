/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:13:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/08 10:47:29 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void init_map(t_caster *c, char **av)
{
    c->map = malloc(sizeof(t_map));
    if (!c->map)
        exit_failure(c, "map malloc failed");
    c->map->map_fd = -2;
    c->map->texture_fd = -2;
    c->map->map_path = av[1];
    c->map->texture_path = NULL;
    c->map->map_arr = NULL;
    c->map->map_width = 0;
    c->map->map_height = 0;
}

static void init_textures(t_caster *c)
{
    // c->textures = malloc(sizeof(t_textures));
    // if (!c->textures)
    //     exit_failure(c, "textures malloc failed");
    // c->textures->north_texture = mlx_load_png("./textures/test_wall2.png");
    // c->textures->south_texture = mlx_load_png("./textures/test_wall5.png");
    // c->textures->east_texture = mlx_load_png("./textures/test_wall3.png");
    // c->textures->west_texture = mlx_load_png("./textures/test_wall4.png");
    // if (!c->textures->north_texture || !c->textures->south_texture || !c->textures->west_texture || !c->textures->east_texture)
    //     exit_failure(c, "Loading textures failed");
    c->textures = malloc(sizeof(t_textures));
    if (!c->textures)
        exit_failure(c, "textures malloc failed");
    c->textures->north_texture = NULL;
    c->textures->south_texture = NULL;
    c->textures->east_texture = NULL;
    c->textures->west_texture = NULL;
    c->textures->floor_color = 0;
    c->textures->ceiling_color = 0;
    c->textures->mmap_space = 0;
    c->textures->mmap_wall = 0;
    c->textures->player = 0;
}

static void init_raycaster(t_caster *c)
{
    c->speed_multiplier = 0.02;
    c->mmap_px = 0;
    c->mmap_py = 0;
    c->view_angle = 0;
    c->plane_x = 0.66;
    c->plane_y = 0;
    c->view_offset = 0;
    c->ray_dir_x = 0;
    c->ray_dir_y = 0;
    c->map_x = 0;
    c->map_y = 0;
    c->dist_increment_x = 0;
    c->dist_increment_y = 0;
    c->step_x = 0;
    c->step_y = 0;
    c->dist_to_grid_x = 0;
    c->dist_to_grid_y = 0;
    c->wall_hit_is_horizontal = 0;
    c->wall_dist = 0;
    c->wall_height = 0;
    c->draw_start = 0;
    c->draw_end = 0;
    c->wall_texture = NULL;
    c->tex_x = 0;
    c->tex_y = 0;
    c->pixel_color = 0;
}

static void init_mlx(t_caster *c)
{
    c->window->handle = mlx_init(WIDTH, HEIGHT, c->window_title, true);
    if (!c->window->handle)
        exit_failure(c, "mlx_init failed");
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    mlx_set_cursor_mode(c->window->handle, MLX_MOUSE_HIDDEN);
    set_images_to_window(c);
    mlx_set_mouse_pos(c->window->handle, WIDTH / 2, HEIGHT / 2);
}

void init(t_caster *c, char **av)
{
    c->window_title = av[0];
    c->window = malloc(sizeof(t_window));
    if (!c->window)
        exit_failure(c, "window struct malloc failed");
    c->window->handle = NULL;
    c->window->view = NULL;
    c->window->minimap = NULL;
    c->window->player = NULL;
    c->px = 0;
    c->py = 0;
    c->cursor_pos = 0;
    init_map(c, av);
    init_textures(c);
    init_raycaster(c);
    init_mlx(c);
}
