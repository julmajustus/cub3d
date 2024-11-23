/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 03:55:17 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/23 00:28:12 by jmakkone         ###   ########.fr       */
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

void	init_sprites(t_caster *c)
{
	int	i;

	c->sp = malloc(sizeof(t_sprite *) * c->max_sprite_count);
	if (!c->sp)
		exit_failure(c, "Failed to allocate memory for sprite array");
	i = -1;
	while (++i < c->max_sprite_count)
	{
		c->sp[i] = malloc(sizeof(t_sprite));
		if (!c->sp[i])
			exit_failure(c, "Failed to allocate memory for sprites");
		ft_bzero(c->sp[i], sizeof(t_sprite));
		c->sp[i]->frame_count = 24;
		c->sp[i]->death_frame_count = 29;
		c->sp[i]->current_frame = 0;
		c->sp[i]->frame_offset = c->sp[i]->current_frame * 64 * 64 * 4;
		c->sp[i]->last_frame_time = 0.0;
		c->sp[i]->speed = 0.22;
		c->sp[i]->x = -1.0;
		c->sp[i]->y = -1.0;
		c->sp[i]->is_visible = 0;
		c->sp[i]->cam_y = 0;
		c->sp[i]->cam_x = 0;
	}
}
