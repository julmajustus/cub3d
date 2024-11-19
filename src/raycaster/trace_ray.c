/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:12 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 09:55:15 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	hit_check(t_caster *c, int x)
{
	is_sprite_visible(c, c->rays[x].map_y, c->rays[x].map_x);
	if (c->map->map_arr[c->rays[x].map_y][c->rays[x].map_x] == 'D' \
		&& !is_door_open(c, c->rays[x].map_y, c->rays[x].map_x))
	{
		c->rays[x].hit_surface = 'D';
		return (1);
	}
	else if (c->map->map_arr[c->rays[x].map_y][c->rays[x].map_x] == 'X')
	{
		c->rays[x].hit_surface = 'X';
		return (1);
	}
	else if (c->map->map_arr[c->rays[x].map_y][c->rays[x].map_x] == '1')
	{
		c->rays[x].hit_surface = '1';
		return (1);
	}
	return (0);
}

void	trace_ray(t_caster *c, int x)
{
	while (1)
	{
		if (c->rays[x].dist_to_grid_x < c->rays[x].dist_to_grid_y)
		{
			c->rays[x].dist_to_grid_x += c->rays[x].dist_increment_x;
			c->rays[x].map_x += c->rays[x].step_x;
			c->rays[x].hit_is_horizontal = 0;
		}
		else
		{
			c->rays[x].dist_to_grid_y += c->rays[x].dist_increment_y;
			c->rays[x].map_y += c->rays[x].step_y;
			c->rays[x].hit_is_horizontal = 1;
		}
		if (hit_check(c, x))
			break ;
	}
}
