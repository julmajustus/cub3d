/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/18 01:01:46 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void move_left_right(t_caster *c, int *moved, double new_px, double x_radius)
{
	if ((int)x_radius > c->map_row_len_buffer[(int)c->py] || c->py > c->map->map_height)
		*moved = 0;
	else if (c->map->map_arr[(int)c->py][(int)x_radius] == 'X')
	{
		if (c->elapsed_time >= (TIMEOUT / 2))
		{
			*moved = 0;
			c->game_status = -2;
		}
		else
		{
			c->px = new_px;
			*moved = 1;
		}
	}
	else if (c->map->map_arr[(int)c->py][(int)x_radius] == '0' || (c->map->map_arr[(int)c->py][(int)x_radius] == 'D' && is_door_open(c, (int)c->py, (int)x_radius)))
	{
		c->px = new_px;
		*moved = 1;
	}
}

void check_collision_left_right(t_caster *c, int *moved, double new_px)
{
	double x_radius;

	x_radius = new_px;
	if (new_px > c->px)
		x_radius = new_px + COLLISION_RADIUS;
	else if (new_px < c->px)
		x_radius = new_px - COLLISION_RADIUS;
	move_left_right (c, moved, new_px, x_radius);
}

void move_up_down(t_caster *c, int *moved, double new_py, double y_radius)
{
	if ((int)y_radius > c->map->map_height || c->px > c->map_row_len_buffer[(int)y_radius])
		*moved = 0;
	else if (c->map->map_arr[(int)y_radius][(int)c->px] == 'X')
	{
		if (c->elapsed_time >= (TIMEOUT / 2))
		{
			*moved = 0;
			c->game_status = -2;
		}
		else
		{
			c->py = new_py;
			*moved = 1;
		}
	}
	else if (c->map->map_arr[(int)y_radius][(int)c->px] == '0' \
	|| (c->map->map_arr[(int)y_radius][(int)c->px] == 'D' && is_door_open(c, (int)y_radius, (int)c->px)))
	{
		c->py = new_py;
		*moved = 1;
	}
}

void check_collision_up_down(t_caster *c, int *moved, double new_py)
{
	double y_radius;

	y_radius = new_py;
	if (new_py > c->py)
		y_radius = new_py + COLLISION_RADIUS;
	else if (new_py < c->py)
		y_radius = new_py - COLLISION_RADIUS;
	move_up_down(c, moved, new_py, y_radius);
}

int check_collision(t_caster *c, double new_px, double new_py)
{
	int moved;

	moved = 0;
	check_collision_left_right(c, &moved, new_px);
	check_collision_up_down(c, &moved, new_py);
	if (moved)
	{
		c->mmap_px = (c->px) * c->map->scale_x;
		c->mmap_py = (c->py) * c->map->scale_y;
	}
	return (moved);
}
