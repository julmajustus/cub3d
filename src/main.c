/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:55:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/01 14:17:44 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init(t_caster *c, char **av)
{
	c->window_title = av[0];
	c->img = malloc(sizeof(t_img));
	if (!c->img)
		exit_failure(c, "img malloc failed");
	c->img->handle = NULL;
	c->img->view = NULL;
	c->img->minimap = NULL;
	c->img->player = NULL;
	c->map = malloc(sizeof(t_map));
	if (!c->map)
		exit_failure(c, "map malloc failed");
	c->map->map_arr = NULL;
	c->map->map_width = 0;
	c->map->map_height = 0;
	c->textures = malloc(sizeof(t_textures));
	if (!c->textures)
		exit_failure(c, "textures malloc failed");
	c->textures->north_texture = mlx_load_png("./textures/test_wall2.png");
	c->textures->south_texture = mlx_load_png("./textures/test_wall5.png");
	c->textures->east_texture = mlx_load_png("./textures/test_wall3.png");
	c->textures->west_texture = mlx_load_png("./textures/test_wall4.png");
	if (!c->textures->north_texture \
		|| !c->textures->south_texture \
		|| !c->textures->west_texture \
		|| !c->textures->east_texture)
		exit_failure(c, "Loading textures failed");
	c->textures->floor_color = 0;
	c->textures->ceiling_color = 0;
	c->speed_multiplier = 0.02;
	c->px = 0;
	c->py = 0;
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

void	reset_images(t_caster *c)
{
	if (c->img->view)
		mlx_delete_image(c->img->handle, c->img->view);
	if (c->img->minimap)
		mlx_delete_image(c->img->handle, c->img->minimap);
	if (c->img->player)
		mlx_delete_image(c->img->handle, c->img->player);
	c->img->view = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	c->img->minimap = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	c->img->player = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	mlx_image_to_window(c->img->handle, c->img->view, 0, 0);
	mlx_image_to_window(c->img->handle, c->img->minimap, 20, 20);
	mlx_image_to_window(c->img->handle, c->img->player, 20, 20);
	c->img->view->instances[0].z = 0;
	c->img->minimap->instances[0].z = 1;
	c->img->player->instances[0].z = 2;
}

void	render_engine(t_caster *c)
{
	printf("FPS: %f\n", 1 / c->img->handle->delta_time);
	//reset_images(c);
	raycaster(c);
	parse_minimap(c);
	if (c->img->player)
		mlx_delete_image(c->img->handle, c->img->player);
	c->img->player = mlx_new_image(c->img->handle, WIDTH, HEIGHT);
	mlx_image_to_window(c->img->handle, c->img->player, 20, 20);
	draw_player_to_minimap(c);
}

void	game_loop(void *param)
{
	t_caster	*c;
	int 		redraw;

	c = (t_caster *)param;
	redraw = 0;

	c->speed_multiplier = c->img->handle->delta_time * 2.2;
	redraw |= movement_up_down(c);
	redraw |= movement_left_right(c);
	redraw |= turn_left_right(c);
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
	window_init(&c);
//	i = -1;
//	while (++i < 4096)
//		printf("Pixel data: %d\n", c.textures->wall_texture->pixels[i]);
	render_engine(&c);
	mlx_loop_hook(c.img->handle, &game_loop, &c);
	mlx_key_hook(c.img->handle, &keyboard_listener, &c);
	mlx_loop(c.img->handle);
	exit_mlx(&c);
	return (0);
}
