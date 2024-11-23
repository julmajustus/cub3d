/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprite_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:03:39 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/23 00:20:32 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	is_sprite_visible(t_caster *c, int y, int x)
{
	int	i;

	i = -1;
	while (++i < c->active_sprite_count)
	{
		if (y == (int)c->sp[i]->y && x == (int)c->sp[i]->x)
			c->sp[i]->is_visible = 1;
	}
}

static void	get_spawn_distance(t_caster *c, int i)
{
	c->sp[i]->dx = c->sp[i]->x - (int)c->px;
	c->sp[i]->dy = c->sp[i]->y - (int)c->py;
	c->sp[i]->dist_to_player = sqrt(c->sp[i]->dx * \
	c->sp[i]->dx + c->sp[i]->dy * c->sp[i]->dy);
}

void	spawn_sprite(t_caster *c)
{
	int	i;

	i = -1;
	while (++i < c->active_sprite_count)
	{
		c->sp_current_time = mlx_get_time();
		if (c->sp[i]->y == -1 && c->sp[i]->x == -1)
		{
			c->sp[i]->is_visible = 0;
			c->spawn_index = ft_abs((long long)((c->sp_current_time \
				* mlx_get_time() * 942983343)) % c->total_spawn_points);
			c->sp[i]->x = c->valid_spawn_points[c->spawn_index].x;
			c->sp[i]->y = c->valid_spawn_points[c->spawn_index].y;
			get_spawn_distance(c, i);
			if (c->sp[i]->dist_to_player < 3)
			{
				c->sp[i]->x = -1;
				c->sp[i]->y = -1;
				i = -1;
				continue ;
			}
			c->sp[i]->last_spwan_time = c->sp_current_time;
		}
	}
}

static int	is_sprite_in_view(t_caster *c, t_sprite *sp, double dy, double dx)
{
	int		ray;
	double	ray_travel_dist;
	double	tolerance;

	tolerance = 0.3;
	ray = (WIDTH / 2) - 10;
	while (++ray < (WIDTH / 2) + 10)
	{
		ray_travel_dist = 0.0;
		c->ta->ray_y = c->py;
		c->ta->ray_x = c->px;
		c->ta->ray_step_y = c->sin_table[ray] * 0.05;
		c->ta->ray_step_x = c->cos_table[ray] * 0.05;
		while (ray_travel_dist < 4.0)
		{
			c->ta->ray_y += c->ta->ray_step_y;
			c->ta->ray_x += c->ta->ray_step_x;
			ray_travel_dist += 0.05;
			dx = c->ta->ray_x - sp->x;
			dy = c->ta->ray_y - sp->y;
			if (sqrt(dx * dx + dy * dy) < tolerance)
				return (1);
		}
	}
	return (0);
}

void	check_sprite_hit(t_caster *c)
{
	int	i;
	int	dx;
	int	dy;
	int	distance_to_sprite;

	i = -1;
	while (++i < c->active_sprite_count)
	{
		dx = c->sp[i]->x - c->px;
		dy = c->sp[i]->y - c->py;
		distance_to_sprite = sqrt(dx * dx + dy * dy);
		if (!c->sp[i]->is_hit && distance_to_sprite < 4.0 \
			&& is_sprite_in_view(c, c->sp[i], dy, dx))
		{
			c->kill_count++;
			c->sp[i]->is_hit = 1;
			c->sp[i]->current_frame = 24;
		}
	}
}
