/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:55:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/13 22:07:39 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_images_to_window(t_caster *c)
{
	c->window->view = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	c->window->gun = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	c->window->minimap = mlx_new_image(c->window->handle, 200, 200);
	mlx_image_to_window(c->window->handle, c->window->view, 0, 0);
	mlx_image_to_window(c->window->handle, c->window->gun, 0, 0);
	mlx_image_to_window(c->window->handle, c->window->minimap, 20, 20);
	c->window->view->instances[0].z = 0;
	c->window->gun->instances[0].z = 2;
	c->window->minimap->instances[0].z = 1;
	init_shotgun(c);
}

void	render_engine(t_caster *c)
{
	printf("FPS: %f\n", 1 / c->window->handle->delta_time);
	printf("Check py: %f px: %f sp pos y: %f x: %f sp collect_count: %d\n"\
		, c->py, c->px, c->sp->y, c->sp->x, c->sp->collect_count);
	raycaster(c);
	parse_minimap(c);
}

void	game_loop(void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	c->cursor_pos = 0;
	c->speed_multiplier = c->window->handle->delta_time * 2.2;
	if (BONUS)
		check_cursor_movement(c);
	movement_up_down(c);
	rotate_view_mouse(c);
	movement_left_right(c);
	rotate_view_keyboard(c);
	render_engine(c);
	if (BONUS && c->sp->is_visible)
		render_squirrel(c);
	gun_fire_animation(c);
}

int	main(int ac, char **av)
{
	t_caster	c;

	if (ac != 2)
	{
		printf("Error, invalid number of arguments.\n");
		return (0);
	}
	init(&c, av);
	read_description(&c);
	printf("Check does it get here\n");
	render_engine(&c);
	render_gun(&c);
	spawn_squirrel(&c);
	printf("Initial sprite location: y: %f x: %f\n", c.sp->y, c.sp->x);
	mlx_loop_hook(c.window->handle, &game_loop, &c);
	mlx_key_hook(c.window->handle, &keyboard_listener, &c);
	mlx_loop(c.window->handle);
	exit_mlx(&c);
	return (0);
}
