/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:55:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/16 12:03:26 by skwon2           ###   ########.fr       */
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

void	render_engine(t_caster *c)
{
	int	i;

	i = -1;
	printf("FPS: %f\n", 1 / c->window->handle->delta_time);
	printf("Check py: %f px: %f\n", c->py, c->px);
	while (++i < c->active_sprite_count)
	{
		printf("Check scale: %d cam_y %f cam_x %f\n", \
		c->sp[i]->scale, c->sp[i]->cam_y, c->sp[i]->cam_x);
		printf("Check screen_y: %d screen_x: %d\n", \
		c->sp[i]->screen_y, c->sp[i]->screen_x);
		printf("Check sp[%d] pos y: %f x: %f is_visible: %d\n", \
		i, c->sp[i]->y, c->sp[i]->x, c->sp[i]->is_visible);
	}
	raycaster(c);
	parse_minimap(c);
}

void	game_loop(void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	c->cursor_pos = 0;
	if (c->game_status == 2)
	{
		check_timeout(c);
		draw_elapsed_time(c);
		c->speed_multiplier = c->window->handle->delta_time * 2.2;
		if (BONUS)
			check_cursor_movement(c);
		movement_up_down(c);
		movement_left_right(c);
		rotate_view_mouse(c);
		rotate_view_keyboard(c);
		render_engine(c);
		if (BONUS)
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
		return (0);
	}
	init(&c, av);
	read_description(&c);
	init_buffers(&c);
	spawn_sprite(&c);
	mlx_loop_hook(c.window->handle, &game_loop, &c);
	mlx_key_hook(c.window->handle, &keyboard_listener, &c);
	mlx_loop(c.window->handle);
	exit_mlx(&c);
	return (0);
}
