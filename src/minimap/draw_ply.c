/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:56:20 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/17 22:51:41 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_player_in_middle(t_caster *c)
{
	c->mmap->cam_x = (int)(c->px * c->map->scale_x) - PLAYER_CENTER;
	c->mmap->cam_y = (int)(c->py * c->map->scale_y) - PLAYER_CENTER;
	if (c->map->map_width * c->map->scale_x < MINIMAP_SIZE)
		c->mmap->cam_x = (c->map->map_width \
			* c->map->scale_x - MINIMAP_SIZE) / 2;
	else if (c->mmap->cam_x > (c->map->map_width \
			* c->map->scale_x) - MINIMAP_SIZE)
		c->mmap->cam_x = (c->map->map_width \
			* c->map->scale_x) - MINIMAP_SIZE;
	if (c->map->map_height * c->map->scale_y < MINIMAP_SIZE)
		c->mmap->cam_y = (c->map->map_height \
			* c->map->scale_y - MINIMAP_SIZE) / 2;
	else if (c->mmap->cam_y > (c->map->map_height \
			* c->map->scale_y) - MINIMAP_SIZE)
		c->mmap->cam_y = (c->map->map_height \
			* c->map->scale_y) - MINIMAP_SIZE;
}

void	restrict_sizes_to_minimap(int *x, int *y)
{
	if (*x < 0)
		*x = 0;
	if (*x >= MINIMAP_SIZE)
		*x = MINIMAP_SIZE - 1;
	if (*y < 0)
		*y = 0;
	if (*y >= MINIMAP_SIZE)
		*y = MINIMAP_SIZE - 1;
}

void	update_player_state(t_caster *c)
{
	static float	prev_view_angle;
	static float	prev_px;
	static float	prev_py;

	prev_view_angle = 0.0f;
	prev_px = 0.0f;
	prev_py = 0.0f;
	if (c->view_angle != prev_view_angle)
		c->player_rotated = 1;
	else
		c->player_rotated = 0;
	if (c->px != prev_px || c->py != prev_py)
		c->player_moved = 1;
	else
		c->player_moved = 0;
	prev_view_angle = c->view_angle;
	prev_px = c->px;
	prev_py = c->py;
}

void	draw_player(t_caster *c)
{
	int	player_x;
	int	player_y;

	player_x = c->mmap_px - c->mmap->cam_x;
	player_y = c->mmap_py - c->mmap->cam_y;
	restrict_sizes_to_minimap(&player_x, &player_y);
	update_player_state(c);
	if (c->player_moved || c->player_rotated)
	{
		c->mmap->ray_len = 0.1;
		draw_ray(c, player_x, player_y);
	}
	draw_tiles(c, player_x, player_y, 2);
}
