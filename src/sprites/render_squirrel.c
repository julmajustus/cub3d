/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_squirrel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:02:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/13 04:02:55 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	update_squirrel_frame(t_sprite *sp)
{
	if (sp->current_frame == 1)
		sp->x += 0.2;
	else if (sp->current_frame == 2)
		sp->y -= 0.2;
	else if (sp->current_frame == 3)
		sp->x -= 0.2;
	else if (sp->current_frame == 4)
		sp->y += 0.2;
	sp->current_frame = (sp->current_frame + 1) % sp->frame_count;
	sp->frame_offset = sp->current_frame * 64 * 64 * 4;
}

void	draw_squirrel_pixel(t_caster *c, int screen_x, int screen_y, int sprite_size)
{
	int		y;
	int		x;
	double	step;

	step = 64.0 / sprite_size;
	y = -1;
	while (++y < sprite_size)
	{
		c->sp->tex_y = (int)(y * step);
		x = -1;
		while (++x < sprite_size)
		{
			c->sp->tex_x = (int)(x * step);
			c->sp->tex_index = c->sp->frame_offset + (c->sp->tex_y * 64 + c->sp->tex_x) * 4;
			c->sp->color = (c->sp->sprite_texture->pixels[c->sp->tex_index] << 24) |
				(c->sp->sprite_texture->pixels[c->sp->tex_index + 1] << 16) |
				(c->sp->sprite_texture->pixels[c->sp->tex_index + 2] << 8) |
				c->sp->sprite_texture->pixels[c->sp->tex_index + 3];
			if ((c->sp->color >> 24) == 0)
				continue;
			if (screen_x + x >= 0 && screen_x + x < WIDTH &&
				screen_y + y >= 0 && screen_y + y < HEIGHT)
				mlx_put_pixel(c->window->view, screen_x + x, screen_y + y, c->sp->color);
		}
	}
}

void	draw_squirrel(t_caster *c, t_sprite *sp)
{
	sp->is_visible = 0;
	sp->dx = sp->x - c->px;
	sp->dy = sp->y - c->py;
	sp->cam_inv = 1.0 / (c->plane_x * sin(c->view_angle) - cos(c->view_angle) * c->plane_y);
	sp->cam_x = sp->cam_inv * (sin(c->view_angle) * sp->dx - cos(c->view_angle) * sp->dy);
	sp->cam_y = sp->cam_inv * (-c->plane_y * sp->dx + c->plane_x * sp->dy);
	if (sp->cam_y > 0)
	{
		sp->screen_x = (int)((WIDTH / 2) * (1 + sp->cam_x / sp->cam_y));
		sp->scale = (int)fabs(HEIGHT / (sp->cam_y * 2));
		sp->screen_y = (HEIGHT / 2) + (sp->scale / 2);
		sp->screen_y += sp->scale / 4;
		draw_squirrel_pixel(c, sp->screen_x - sp->scale / 2, sp->screen_y, sp->scale);
	}
}

void	render_squirrel(t_caster *c)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - c->sp->last_frame_time >= 0.15)
	{
		update_squirrel_frame(c->sp);
		c->sp->last_frame_time = current_time;
	}
	draw_squirrel(c, c->sp);
}
