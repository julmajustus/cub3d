/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:55:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/01 20:50:37 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_images_to_window(t_caster *c)
{
	c->window->view = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	c->window->minimap = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	c->window->player = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	mlx_image_to_window(c->window->handle, c->window->view, 0, 0);
	mlx_image_to_window(c->window->handle, c->window->minimap, 20, 20);
	mlx_image_to_window(c->window->handle, c->window->player, 20, 20);
	c->window->view->instances[0].z = 0;
	c->window->minimap->instances[0].z = 1;
	c->window->player->instances[0].z = 2;
}

void	render_engine(t_caster *c)
{
	printf("FPS: %f\n", 1 / c->window->handle->delta_time);
	raycaster(c);
	parse_minimap(c);
	if (c->window->player)
		mlx_delete_image(c->window->handle, c->window->player);
	c->window->player = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
	mlx_image_to_window(c->window->handle, c->window->player, 20, 20);
	draw_player_to_minimap(c);
}

void	game_loop(void *param)
{
	t_caster	*c;
	int 		redraw;

	c = (t_caster *)param;
	redraw = 0;
	c->cursor_pos = 0;
	c->speed_multiplier = c->window->handle->delta_time * 2.2;
	check_cursor_movement(c);
	redraw |= movement_up_down(c);
	redraw |= movement_left_right(c);
	redraw |= rotate_view_keyboard(c);
	redraw |= rotate_view_mouse(c);
	if (redraw)
		render_engine(c);
}

int	main(int ac, char **av)
{
	t_caster c;

	if (ac != 2)
	{
		printf("Error, invalid number of arguments.\n");
		return (0);
	}
	init(&c, av);
	read_map(&c, av);
	int i = -1;
	while (c.map->map_arr[++i])
		printf("%s", c.map->map_arr[i]);
//	i = -1;
//	while (++i < 4096)
//		printf("Pixel data: %d\n", c.textures->wall_texture->pixels[i]);
	render_engine(&c);
	mlx_loop_hook(c.window->handle, &game_loop, &c);
	mlx_key_hook(c.window->handle, &keyboard_listener, &c);
	mlx_loop(c.window->handle);
	exit_mlx(&c);
	return (0);
}
