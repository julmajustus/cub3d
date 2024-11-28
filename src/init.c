/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:13:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/28 11:12:13 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_toggle_action(t_caster *c)
{
	c->ta = malloc(sizeof(t_toggle_action));
	if (!c->ta)
		exit_failure(c, "ta struct malloc failed");
	ft_bzero(c->ta, sizeof(t_toggle_action));
}

static void	init_map(t_caster *c, char **av)
{
	c->map = malloc(sizeof(t_map));
	if (!c->map)
		exit_failure(c, "map struct malloc failed");
	ft_bzero(c->map, sizeof(t_map));
	c->map->map_fd = -2;
	c->map->texture_fd = -2;
	c->map->map_path = av[1];
	c->mmap = malloc(sizeof(t_minmap));
	if (!c->mmap)
		exit_failure(c, "minimap struct malloc failed");
	c->mmap->wall = mlx_load_png("./textures/wall.png");
	c->mmap->space = mlx_load_png("./textures/space.png");
	c->mmap->door = mlx_load_png("./textures/door.png");
	if (!c->mmap->wall || !c->mmap->space || !c->mmap->door)
		exit_failure(c, "Failed to load textures");
}

static void	init_textures(t_caster *c)
{
	c->textures = malloc(sizeof(t_textures));
	if (!c->textures)
		exit_failure(c, "textures struct malloc failed");
	ft_bzero(c->textures, sizeof(t_textures));
	c->textures->menu_screen = mlx_load_png("./textures/howto.png");
	c->textures->start_screen = mlx_load_png("./textures/start_screen.png");
	c->textures->death_screen = mlx_load_png("./textures/death_screen.png");
	c->textures->succeed_screen = mlx_load_png("./textures/succeed_screen.png");
	c->textures->press_r = mlx_load_png("./textures/press_R.png");
	c->textures->exit = mlx_load_png("./textures/brickexit2.png");
	c->textures->press_enter = mlx_load_png("./textures/press_Enter.png");
	c->textures->press_menu_enter = mlx_load_png("./textures/menu_enter.png");
	c->textures->sp_texture = mlx_load_png("./textures/zombie_with_death.png");
	c->textures->c_texture = mlx_load_png("./textures/brickceiling2.png");
	c->textures->f_texture = mlx_load_png("./textures/brickfloor3.png");
	c->textures->door_texture = mlx_load_png("./textures/brickdoordark3.png");
	if (!c->textures->menu_screen || !c->textures->start_screen \
		|| !c->textures->death_screen || !c->textures->sp_texture \
		|| !c->textures->c_texture || !c->textures->f_texture \
		|| !c->textures->press_enter || !c->textures->press_r \
		|| !c->textures->exit || !c->textures->door_texture)
		exit_failure(c, "Failed to load textures");
}

static void	init_mlx(t_caster *c)
{
	c->window->handle = mlx_init(WIDTH, HEIGHT, c->window_title, true);
	if (!c->window->handle)
		exit_failure(c, "mlx_init failed");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_cursor_mode(c->window->handle, MLX_MOUSE_HIDDEN);
	set_images_to_window(c);
}

void	init(t_caster *c, char **av)
{
	ft_bzero(c, sizeof(t_caster));
	c->window_title = av[0];
	c->window = malloc(sizeof(t_window));
	if (!c->window)
		exit_failure(c, "window struct malloc failed");
	ft_bzero(c->window, sizeof(t_window));
	c->speed_multiplier = 0.02;
	c->plane_x = 0.66;
	c->is_sprite_visible = 1;
	c->max_sprite_count = 150;
	c->active_sprite_count = ZOMBIE_COUNT;
	init_map(c, av);
	init_shotgun(c);
	init_sprites(c);
	init_textures(c);
	init_mlx(c);
	init_toggle_action(c);
}
