/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:54:48 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 10:38:39 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	precalculate_ray_directions(t_caster *c)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		c->rays[x].view_offset = 2 * x / (double)WIDTH - 1;
		c->cos_table[x] = cos(c->view_angle) + c->plane_x * c->rays[x].view_offset;
		c->sin_table[x] = sin(c->view_angle) + c->plane_y * c->rays[x].view_offset;
	}
}

static void	init_ray_dir_and_cast_position(t_caster *c, int x)
{
	c->rays[x].dist_increment_x = fabs(1 / c->rays[x].dx);
	c->rays[x].dist_increment_y = fabs(1 / c->rays[x].dy);
	if (c->rays[x].dx < 0)
	{
		c->rays[x].step_x = -1;
		c->rays[x].dist_to_grid_x = (c->px - c->rays[x].map_x) * c->rays[x].dist_increment_x;
	}
	else
	{
		c->rays[x].step_x = 1;
		c->rays[x].dist_to_grid_x = (c->rays[x].map_x + 1.0 - c->px) * c->rays[x].dist_increment_x;
	}
	if (c->rays[x].dy < 0)
	{
		c->rays[x].step_y = -1;
		c->rays[x].dist_to_grid_y = (c->py - c->rays[x].map_y) * c->rays[x].dist_increment_y;
	}
	else
	{
		c->rays[x].step_y = 1;
		c->rays[x].dist_to_grid_y = (c->rays[x].map_y + 1.0 - c->py) * c->rays[x].dist_increment_y;
	}
}

static void	get_wall_dist_and_height(t_caster *c, int x)
{
	if (c->rays[x].hit_is_horizontal == 0)
		c->rays[x].wall_dist = (c->rays[x].map_x - c->px + \
			(1 - c->rays[x].step_x) / 2) / c->rays[x].dx;
	else
		c->rays[x].wall_dist = (c->rays[x].map_y - c->py + \
			(1 - c->rays[x].step_y) / 2) / c->rays[x].dy;
	c->rays[x].wall_height = (int)(HEIGHT / c->rays[x].wall_dist);
	c->rays[x].draw_start = -c->rays[x].wall_height / 2 + HEIGHT / 2;
	if (c->rays[x].draw_start < 0 || c->rays[x].draw_start > HEIGHT)
		c->rays[x].draw_start = 0;
	c->rays[x].draw_end = c->rays[x].wall_height / 2 + HEIGHT / 2;
	if (c->rays[x].draw_end >= HEIGHT || c->rays[x].draw_end < 0)
		c->rays[x].draw_end = HEIGHT;
}

void	cast_rays(t_caster *c)
{
	int	x;

	precalculate_ray_directions(c);
	x = -1;
	while (++x < WIDTH)
	{
		c->rays[x].dx = c->cos_table[x];
		c->rays[x].dy = c->sin_table[x];
		c->rays[x].map_x = (int)c->px;
		c->rays[x].map_y = (int)c->py;
		init_ray_dir_and_cast_position(c, x);
		trace_ray(c, x);
		get_wall_dist_and_height(c, x);
	}
}
