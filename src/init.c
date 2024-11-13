/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:13:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/13 00:12:58 by jmakkone         ###   ########.fr       */
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
}

static void	init_textures(t_caster *c)
{
	c->textures = malloc(sizeof(t_textures));
	if (!c->textures)
		exit_failure(c, "textures struct malloc failed");
	ft_bzero(c->textures, sizeof(t_textures));
}

static void	init_mlx(t_caster *c)
{
	c->window->handle = mlx_init(WIDTH, HEIGHT, c->window_title, true);
	if (!c->window->handle)
		exit_failure(c, "mlx_init failed");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_cursor_mode(c->window->handle, MLX_MOUSE_HIDDEN);
	set_images_to_window(c);
	mlx_set_mouse_pos(c->window->handle, WIDTH / 2, HEIGHT / 2);
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
	c->plane_x = 0.66;// * sin(c->view_angle);
	//c->plane_y = 0.66;// * cos(c->view_angle);
	init_map(c, av);
	init_textures(c);
	init_mlx(c);
	init_toggle_action(c);
	init_squirrel(c);
	init_shotgun(c);
}
