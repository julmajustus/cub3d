/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:17:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/29 15:22:34 by skwon2           ###   ########.fr       */
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

static void	init_ray_dir_and_cast_position(t_caster *c, int x)
{
	c->dist_increment_x = fabs(1 / c->cos_table[x]);
	c->dist_increment_y = fabs(1 / c->sin_table[x]);
	if (c->cos_table[x] < 0)
	{
		c->step_x = -1;
		c->dist_to_grid_x = (c->px - c->map_x) * c->dist_increment_x;
	}
	else
	{
		c->step_x = 1;
		c->dist_to_grid_x = (c->map_x + 1.0 - c->px) * c->dist_increment_x;
	}
	if (c->sin_table[x] < 0)
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

static void	get_wall_dist_and_height(t_caster *c, int x)
{
	if (c->hit_is_horizontal[x] == 0)
		c->wall_dist[x] = (c->map_x - c->px + \
			(1 - c->step_x) / 2) / c->cos_table[x];
	else
		c->wall_dist[x] = (c->map_y - c->py + \
			(1 - c->step_y) / 2) / c->sin_table[x];
	c->wall_height[x] = (int)(HEIGHT / c->wall_dist[x]);
	c->draw_start[x] = -c->wall_height[x] / 2 + HEIGHT / 2;
	if (c->draw_start[x] < 0 || c->draw_start[x] > HEIGHT)
		c->draw_start[x] = 0;
	c->draw_end[x] = c->wall_height[x] / 2 + HEIGHT / 2;
	if (c->draw_end[x] >= HEIGHT || c->draw_end[x] < 0)
		c->draw_end[x] = HEIGHT;
}

void	cast_rays(t_caster *c)
{
	int	x;

	precalculate_ray_directions(c);
	x = -1;
	while (++x < WIDTH)
	{
		c->map_x = (int)c->px;
		c->map_y = (int)c->py;
		init_ray_dir_and_cast_position(c, x);
		trace_ray(c, x);
		get_wall_dist_and_height(c, x);
	}
}
