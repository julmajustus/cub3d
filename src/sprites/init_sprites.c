/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:55:17 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/14 01:03:46 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	c->sp = malloc(sizeof(t_sprite));
	if (!c->sp)
		exit_failure(c, "Failed to allocate memory for squirrel sprite");
	c->sp->texture = mlx_load_png("./textures/squirrel.png");
	if (!c->sp->texture)
		exit_failure(c, "Failed to load sprite texture");
	c->sp->frame_count = 5;
	c->sp->current_frame = 0;
	c->sp->frame_offset = c->sp->current_frame * 64 * 64 * 4;
	c->sp->last_frame_time = 0.0;
	c->sp->x = 0.0;
	c->sp->y = 0.0;
	c->sp->is_visible = 0;
	c->sp->collect_count = 0;
	c->sp->last_frame_time = mlx_get_time();
}
