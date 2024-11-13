/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shotgun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:48:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/13 04:43:08 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	update_gun_frame(t_sprite *g)
{
	g->current_frame = (g->current_frame + 1) % g->frame_count;
	g->frame_offset = g->current_frame * 64 * 64 * 4;
}

void	start_gun_fire_animation(t_sprite *gun)
{
	gun->current_frame = 0;
	gun->is_animating = 1;
	gun->remaining_frames = 5;
	gun->last_frame_time = mlx_get_time();
}

void	gun_fire_animation(t_caster *c)
{
	double	current_time;
	double	frame_delay;

	if (c->gun->is_animating)
	{
		current_time = mlx_get_time();
		frame_delay = 0.10;
		if (current_time - c->gun->last_frame_time >= frame_delay)
		{
			mlx_delete_image(c->window->handle, c->window->gun);
			c->window->gun = mlx_new_image(c->window->handle, WIDTH, HEIGHT);
			mlx_image_to_window(c->window->handle, c->window->gun, 0, 0);
			c->window->gun->instances[0].z = 2;
			update_gun_frame(c->gun);
			render_gun(c);
			c->gun->last_frame_time = current_time;
			c->gun->remaining_frames--;
			if (c->gun->remaining_frames <= 0)
			{
				c->gun->is_animating = 0;
				c->gun->current_frame = 0;
			}
		}
	}
}

void	draw_gun_pixel(t_caster *c, int scr_x, int scr_y, int size)
{
	int		y;
	int		x;
	double	step;

	step = 64.0 / size;
	y = -1;
	while (++y < size)
	{
		c->gun->tex_y = (int)(y * step);
		x = -1;
		while (++x < size)
		{
			c->gun->tex_x = (int)(x * step);
			c->gun->tex_index = c->gun->frame_offset \
				+ (c->gun->tex_y * 64 + c->gun->tex_x) * 4;
			c->gun->color = (c->gun->texture->pixels[c->gun->tex_index] << 24) \
				| (c->gun->texture->pixels[c->gun->tex_index + 1] << 16) \
				| (c->gun->texture->pixels[c->gun->tex_index + 2] << 8) \
				| c->gun->texture->pixels[c->gun->tex_index + 3];
			if (scr_x + x >= 0 && scr_x + x < WIDTH \
				&& scr_y + y >= 0 && scr_y + y < HEIGHT)
				mlx_put_pixel(c->window->gun, scr_x + x, \
								scr_y + y, c->gun->color);
		}
	}
}

void	render_gun(t_caster *c)
{
	draw_gun_pixel(c, 733, 626, 454);
}
