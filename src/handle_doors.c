/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:39:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/18 00:45:40 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_door	*find_door_at(t_caster *c, int map_y, int map_x)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < c->door_count)
	{
		door = &c->doors[i];
		if (door->y == map_y && door->x == map_x)
			return (door);
	}
	return (NULL);
}

t_door	*find_door_in_view(t_caster *c, double max_distance)
{
	double	ray_travel_dist;

	ray_travel_dist = 0.0;
	c->ta->ray_y = c->py;
	c->ta->ray_x = c->px;
	c->ta->ray_step_y = c->sin_table[WIDTH / 2] * 0.2;
	c->ta->ray_step_x = c->cos_table[WIDTH / 2] * 0.2;
	while (ray_travel_dist < max_distance)
	{
		c->ta->map_y = (int)c->ta->ray_y;
		c->ta->map_x = (int)c->ta->ray_x;
		if (c->ta->map_y == (int)c->py \
			&& c->ta->map_x == (int)c->px \
			&& c->map->map_arr[(int)c->py][(int)c->px] == 'D')
			;
		else if (c->map->map_arr[c->ta->map_y][c->ta->map_x] == 'D')
			return (find_door_at(c, c->ta->map_y, c->ta->map_x));
		c->ta->ray_y += c->ta->ray_step_y;
		c->ta->ray_x += c->ta->ray_step_x;
		ray_travel_dist += 0.2;
	}
	return (NULL);
}

int	is_door_open(t_caster *c, int y, int x)
{
	t_door	*door;

	door = find_door_at(c, y, x);
	if (door)
		return (door->is_open);
	return (0);
}

void	toggle_door(t_caster *c, double max_distance)
{
	t_door	*door;

	door = find_door_in_view(c, max_distance);
	if (door)
	{
		printf("Trying to open door! is door open %d\n", door->is_open);
		if (!door->is_open)
			door->is_open = 1;
		else
			door->is_open = 0;
	}
}

void	store_door_info(t_caster *c, const char *line)
{
	int		x;
	int		y;
	t_door	*new_door;

	x = -1;
	y = c->map->map_height;
	if (!c->textures->door_texture)
		c->textures->door_texture = \
			mlx_load_png("./textures/brickdoordark2.png");
	while (line[++x])
	{
		if (line[x] == 'D')
		{
			c->doors = ft_realloc(c->doors, (sizeof(t_door) * c->door_count), \
				(sizeof(t_door) * (c->door_count + 1)));
			if (!c->doors)
				exit_failure(c, "Failed to allocate memory for doors");
			new_door = &c->doors[c->door_count];
			new_door->x = x;
			new_door->y = y;
			new_door->is_open = 0;
			c->door_count++;
		}
	}
}
