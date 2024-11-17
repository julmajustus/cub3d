/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:54:48 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/17 16:29:53 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	precalculate_ray_directions(t_caster *c)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		c->view_offset = 2 * x / (double)WIDTH - 1;
		c->cos_table[x] = cos(c->view_angle) + c->plane_x * c->view_offset;
		c->sin_table[x] = sin(c->view_angle) + c->plane_y * c->view_offset;
	}
}

static void	init_ray_dir_and_cast_position(t_caster *c)
{
	c->dist_increment_x = fabs(1 / c->ray_dir_x);
	c->dist_increment_y = fabs(1 / c->ray_dir_y);
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->dist_to_grid_x = (c->px - c->map_x) * c->dist_increment_x;
	}
	else
	{
		c->step_x = 1;
		c->dist_to_grid_x = (c->map_x + 1.0 - c->px) * c->dist_increment_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->dist_to_grid_y = (c->py - c->map_y) * c->dist_increment_y;
	}
	else
	{
		c->step_y = 1;
		c->dist_to_grid_y = (c->map_y + 1.0 - c->py) * c->dist_increment_y;
	}
}

static void	get_wall_dist_and_height(t_caster *c)
{
	if (c->wall_hit_is_horizontal == 0)
		c->wall_dist = (c->map_x - c->px + \
			(1 - c->step_x) / 2) / c->ray_dir_x;
	else
		c->wall_dist = (c->map_y - c->py + \
			(1 - c->step_y) / 2) / c->ray_dir_y;
	c->wall_height = (int)(HEIGHT / c->wall_dist);
	c->draw_start = -c->wall_height / 2 + HEIGHT / 2;
	if (c->draw_start < 0)
		c->draw_start = 0;
	c->draw_end = c->wall_height / 2 + HEIGHT / 2;
	if (c->draw_end >= HEIGHT)
		c->draw_end = HEIGHT;
}

void	raycaster(t_caster *c)
{
	int	x;

	precalculate_ray_directions(c);
	x = -1;
	while (++x < WIDTH)
	{
		c->ray_dir_x = c->cos_table[x];
		c->ray_dir_y = c->sin_table[x];
		c->map_x = (int)c->px;
		c->map_y = (int)c->py;
		init_ray_dir_and_cast_position(c);
		trace_ray_until_wall_hit(c);
		get_wall_dist_and_height(c);
		c->depth_buffer[x] = c->wall_dist;
		get_wall_texture(c);
		get_texture_offset(c);
		render_wall_column(c, x);
		render_floor_and_ceiling(c, c->draw_end, x);
	}
}
