/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:55:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/28 10:11:18 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_images_to_window(t_caster *c)
{
	if (c->window->view)
		mlx_delete_image(c->window->handle, c->window->view);
	if (c->window->gun)
		mlx_delete_image(c->window->handle, c->window->gun);
	if (c->window->minimap)
		mlx_delete_image(c->window->handle, c->window->minimap);
	c->window->view = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	c->window->gun = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	c->window->minimap = mlx_new_image(c->window->handle, 200, 200);
	mlx_image_to_window(c->window->handle, c->window->view, 0, 0);
	mlx_image_to_window(c->window->handle, c->window->gun, 0, 0);
	mlx_image_to_window(c->window->handle, c->window->minimap, 20, 20);
	c->window->view->instances[0].z = 0;
	c->window->gun->instances[0].z = 2;
	c->window->minimap->instances[0].z = 1;
}

void	game_loop(void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	if (c->game_status == 2)
	{
		c->speed_multiplier = c->window->handle->delta_time * 2.2;
		movement_up_down(c);
		movement_left_right(c);
		rotate_view_keyboard(c);
		printf("FPS: %f\n", 1 / c->window->handle->delta_time);
		cast_rays(c);
		render_view(c);
	}
	else
		check_game_status(c);
}

void	game_loop_bonus(void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	if (c->game_status == 2)
	{
		c->speed_multiplier = c->window->handle->delta_time * 2.2;
		c->cursor_pos = 0;
		check_cursor_movement(c);
		movement_up_down(c);
		movement_left_right(c);
		rotate_view_keyboard(c);
		rotate_view_mouse(c);
		printf("FPS: %f\n", 1 / c->window->handle->delta_time);
		cast_rays(c);
		render_view(c);
		parse_minimap(c);
		check_timeout(c);
		draw_elapsed_time(c);
		draw_kill_count(c);
		render_sprites(c);
		gun_fire_animation(c);
	}
	else
		check_game_status(c);
}

int	main(int ac, char **av)
{
	t_caster	c;

	if (ac != 2)
	{
		printf("Error, invalid number of arguments.\n");
		return (1);
	}
	init(&c, av);
	read_description(&c);
	init_buffers(&c);
	init_pixel_color_buffers(&c);
	if (BONUS)
	{
		spawn_sprite(&c);
		mlx_loop_hook(c.window->handle, &game_loop_bonus, &c);
	}
	else
		mlx_loop_hook(c.window->handle, &game_loop, &c);
	mlx_key_hook(c.window->handle, &keyboard_listener, &c);
	mlx_loop(c.window->handle);
	exit_mlx(&c);
	return (0);
}
