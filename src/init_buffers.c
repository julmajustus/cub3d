/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:25:40 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 21:50:55 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_buffers(t_caster *c)
{
	int	i;

	c->map_row_len_buffer = malloc(sizeof(int) * c->map->map_height);
	if (!c->map_row_len_buffer)
		exit_failure(c, "Failed to allocate memory for map row length buffer");
	i = -1;
	while (++i < c->map->map_height)
		c->map_row_len_buffer[i] = ft_strlen(c->map->map_arr[i]);
	i = -1;
	while (++i < HEIGHT)
	{
		if (i < HEIGHT / 2)
			c->fc_row_dist_buffer[i] = HEIGHT / (HEIGHT - 2.0 * i);
		else
			c->fc_row_dist_buffer[i] = HEIGHT / (2.0 * i - HEIGHT);
	}
	init_spawn_points(c);
}

void	init_spawn_points(t_caster *c)
{
	int	y;
	int	x;
	int	count;

	c->valid_spawn_points = \
		malloc(c->map->map_height * c->map->map_width * sizeof(t_spawn_point));
	if (!c->valid_spawn_points)
		exit_failure(c, "Failed to allocate memory for valid_spawn_points");
	count = 0;
	y = -1;
	while (++y < c->map->map_height)
	{
		x = -1;
		while (++x < c->map_row_len_buffer[y])
		{
			if (c->map->map_arr[y][x] == '0')
			{
				c->valid_spawn_points[count].x = x;
				c->valid_spawn_points[count].y = y;
				count++;
			}
		}
	}
	c->total_spawn_points = count;
}
