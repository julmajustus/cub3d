/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/10 14:16:54 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	check_collision_left_right(t_caster *c, int *moved, double new_px)
{
	double	x_radius;

	x_radius = new_px;
	if (new_px > c->px)
		x_radius = new_px + COLLISION_RADIUS;
	else if (new_px < c->px)
		x_radius = new_px - COLLISION_RADIUS;
	if (c->map->map_arr[(int)c->py][(int)x_radius] == '0' \
		|| (c->map->map_arr[(int)c->py][(int)x_radius] == 'D' \
		&& is_door_open(c, (int)c->py, (int)x_radius)))
	{
		c->px = new_px;
		*moved = 1;
	}
}

static void	check_collision_up_down(t_caster *c, int *moved, double new_py)
{
	double	y_radius;

	y_radius = new_py;
	if (new_py > c->py)
		y_radius = new_py + COLLISION_RADIUS;
	else if (new_py < c->py)
		y_radius = new_py - COLLISION_RADIUS;
	if (c->map->map_arr[(int)y_radius][(int)c->px] == '0' \
		|| (c->map->map_arr[(int)y_radius][(int)c->px] == 'D' \
		&& is_door_open(c, (int)y_radius, (int)c->px)))
	{
		c->py = new_py;
		*moved = 1;
	}
}

int	check_collision(t_caster *c, double new_px, double new_py)
{
	int	moved;

	moved = 0;
	check_collision_left_right(c, &moved, new_px);
	check_collision_up_down(c, &moved, new_py);
	if (moved)
	{
		c->mmap_px = (c->px - 0.25) * c->map->scale_x + 0.25;
		c->mmap_py = (c->py - 0.25) * c->map->scale_y + 0.25;
	}
	return (moved);
}
