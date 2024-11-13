/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_squirrel_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:03:39 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/13 04:04:13 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	spawn_squirrel(t_caster *c)
{
	double	current_time;
	int		seed_y;
	int		seed_x;
	int		new_spawn;

	new_spawn = 0;
	current_time = mlx_get_time();
	while (!new_spawn)
	{
		seed_y = ft_abs((size_t)(current_time * mlx_get_time() \
				  * -923423) % c->map->map_height);
		seed_x = ft_abs((size_t)(current_time * mlx_get_time() \
				  * 72393823) % c->map->map_width);
		if (seed_y < c->map->map_height)
		{
			if ((size_t)seed_x < ft_strlen(c->map->map_arr[seed_y]) \
				&& c->map->map_arr[seed_y][seed_x] == '0')
			{
				c->sp->y = seed_y;
				c->sp->x = seed_x;
				new_spawn = 1;
				c->sp->last_spwan_time = current_time;
			}
		}
	}
}

int	is_squirrel_in_view(t_caster *c, double dy, double dx, double max_distance)
{
	int		ray;
	double	ray_travel_dist;
	double	tolerance = 0.5;

	ray = (WIDTH / 2) - 10;
	while (++ray < (WIDTH / 2) + 10)
	{
		ray_travel_dist = 0.0;
		c->ta->ray_y = c->py;
		c->ta->ray_x = c->px;
		c->ta->ray_step_y = c->sin_table[ray] * 0.05;
		c->ta->ray_step_x = c->cos_table[ray] * 0.05;
		while (ray_travel_dist < max_distance)
		{
			c->ta->ray_y += c->ta->ray_step_y;
			c->ta->ray_x += c->ta->ray_step_x;
			ray_travel_dist += 0.05;
			dx = c->ta->ray_x - c->sp->x;
			dy = c->ta->ray_y - c->sp->y;
			if (sqrt(dx * dx + dy * dy) < tolerance)
				return (1);
		}
	}
	return (0);
}

void	check_squirrel_hit(t_caster *c)
{
	//spawn_sprite(c);
	double	dx;
	double	dy;
	double	distance_to_squirrel;

	dx = c->sp->x - c->px;
	dy = c->sp->y - c->py;
	distance_to_squirrel = sqrt(dx * dx + dy * dy);
	if (distance_to_squirrel < 4.0 && is_squirrel_in_view(c, dy, dx, 4.0))
	{
		c->sp->x = -1;
		c->sp->y = -1;
		spawn_squirrel(c);
		c->sp->collect_count += 1;
	}
}
