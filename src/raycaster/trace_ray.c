/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:12 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/18 15:41:05 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	hit_check(t_caster *c, int x)
{
	is_sprite_visible(c, c->map_y, c->map_x);
	if (c->map->map_arr[c->map_y][c->map_x] == 'D' \
		&& !is_door_open(c, c->map_y, c->map_x))
	{
		c->hit_surface[x] = 'D';
		return (1);
	}
	else if (c->map->map_arr[c->map_y][c->map_x] == 'X')
	{
		c->hit_surface[x] = 'X';
		return (1);
	}
	else if (c->map->map_arr[c->map_y][c->map_x] == '1')
	{
		c->hit_surface[x] = '1';
		return (1);
	}
	return (0);
}

void	trace_ray(t_caster *c, int x)
{
	while (1)
	{
		if (c->dist_to_grid_x < c->dist_to_grid_y)
		{
			c->dist_to_grid_x += c->dist_increment_x;
			c->map_x += c->step_x;
			c->hit_is_horizontal[x] = 0;
		}
		else
		{
			c->dist_to_grid_y += c->dist_increment_y;
			c->map_y += c->step_y;
			c->hit_is_horizontal[x] = 1;
		}
		if (hit_check(c, x))
			break ;
	}
}
