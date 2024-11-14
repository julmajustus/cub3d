/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:55:17 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/14 15:55:36 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
		while (++x < (int)ft_strlen(c->map->map_arr[y]))
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

void	init_shotgun(t_caster *c)
{
	c->gun = malloc(sizeof(t_sprite));
	if (!c->gun)
		exit_failure(c, "Failed to allocate memory for shotgun sprite");
	c->gun->texture = mlx_load_png("./textures/shotgun_sprite.png");
	if (!c->gun->texture)
		exit_failure(c, "Failed to load shotgun texture");
	c->gun->tex_y = 0;
	c->gun->tex_x = 0;
	c->gun->frame_count = 5;
	c->gun->current_frame = 0;
	c->gun->frame_offset = c->gun->current_frame * 64 * 64 * 4;
	c->gun->tex_index = 0;
	c->gun->last_frame_time = 0.0;
	c->gun->is_animating = 0;
	c->gun->remaining_frames = 0;
}

void	init_squirrel(t_caster *c)
{
	int	i;

	i = -1;
	c->textures->sp_texture = mlx_load_png("./textures/squirrel.png");
	if (!c->textures->sp_texture)
		exit_failure(c, "Failed to load sprite texture");
	c->sp = malloc(sizeof(t_sprite *) * c->max_sprite_count);
	if (!c->sp)
		exit_failure(c, "Failed to allocate memory for squirrel sprite");
	while (++i < c->max_sprite_count)
	{
		c->sp[i] = malloc(sizeof(t_sprite));
		if (!c->sp[i])
			exit_failure(c, "Failed to allocate memory for squirrel sprite");
		c->sp[i]->frame_count = 5;
		c->sp[i]->current_frame = 0;
		c->sp[i]->frame_offset = c->sp[i]->current_frame * 64 * 64 * 4;
		c->sp[i]->last_frame_time = 0.0;
		c->sp[i]->x = -1.0;
		c->sp[i]->y = -1.0;
		c->sp[i]->is_visible = 0;
		c->sp[i]->last_frame_time = mlx_get_time();
	}
}
