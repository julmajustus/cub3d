/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_squirrel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:02:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/14 15:55:15 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	update_squirrel_position(t_caster *c, t_sprite *sp)
{
	if (sp->dist_to_player > 0)
	{
		sp->dx /= sp->dist_to_player;
		sp->dy /= sp->dist_to_player;
	}
	sp->speed = 0.10;
	sp->x += sp->dx * sp->speed;
	sp->y += sp->dy * sp->speed;
	sp->next_tile_x = (int)(sp->x);
	sp->next_tile_y = (int)(sp->y);
	if (c->map->map_arr[sp->next_tile_y][sp->next_tile_x] == '1')
	{
		if (c->map->map_arr[(int)sp->y] \
			[(int)(sp->x - sp->dx * sp->speed)] != '1')
			sp->x -= sp->dx * sp->speed;
		else if (c->map->map_arr[(int)(sp->y - sp->dy * sp->speed)] \
				[(int)sp->x] != '1')
			sp->y -= sp->dy * sp->speed;
		else
		{
			sp->x -= sp->dx * sp->speed;
			sp->y -= sp->dy * sp->speed;
		}
	}
}

static void	update_squirrel_texture_frame(t_sprite *sp)
{
	sp->current_frame = (sp->current_frame + 1) % sp->frame_count;
	sp->frame_offset = sp->current_frame * 64 * 64 * 4;
}

static void	draw_squirrel(t_caster *c, t_sprite *sp, int size)
{
	int		y;
	int		x;

	y = -1;
	while (++y < size)
	{
		sp->tex_y = (int)(y * TEXTURE_WIDTH / size);
		x = -1;
		while (++x < size)
		{
			sp->tex_x = (int)(x * TEXTURE_WIDTH / size);
			sp->tex_index = sp->frame_offset \
				+ (sp->tex_y * 64 + sp->tex_x) * 4;
			sp->color = (c->textures->sp_texture->pixels[sp->tex_index] << 24) \
				| (c->textures->sp_texture->pixels[sp->tex_index + 1] << 16) \
				| (c->textures->sp_texture->pixels[sp->tex_index + 2] << 8) \
				| c->textures->sp_texture->pixels[sp->tex_index + 3];
			if ((sp->color >> 24) == 0)
				continue ;
			if (sp->screen_x + x >= 0 && sp->screen_x + x < WIDTH \
				&& sp->screen_y + y >= 0 && sp->screen_y + y < HEIGHT)
				mlx_put_pixel(c->window->view, \
					sp->screen_x + x, sp->screen_y + y, sp->color);
		}
	}
}

static void	get_squirrel_size_and_pos(t_caster *c, t_sprite *sp)
{
	sp->is_visible = 0;
	sp->dx = sp->x - c->px;
	sp->dy = sp->y - c->py;
	sp->cam_inv = 1.0 / (c->plane_x * sin(c->view_angle) \
		- cos(c->view_angle) * c->plane_y);
	sp->cam_x = sp->cam_inv * (sin(c->view_angle) * sp->dx \
		- cos(c->view_angle) * sp->dy);
	sp->cam_y = sp->cam_inv * (-c->plane_y * sp->dx + c->plane_x * sp->dy);
	if (sp->cam_y > 0)
	{
		sp->screen_x = (int)((WIDTH / 2) * (1 + sp->cam_x / sp->cam_y));
		sp->scale = (int)fabs(HEIGHT / (sp->cam_y * 2));
		sp->screen_y = (HEIGHT / 2) + (sp->scale / 2);
		sp->screen_y += sp->scale / 4;
		sp->screen_x = sp->screen_x - sp->scale / 2;
		draw_squirrel(c, sp, sp->scale);
	}
}

void	render_squirrel(t_caster *c)
{
	int		i;
	double	current_time;

	i = -1;
	while (++i < c->active_sprite_count)
	{
		if (!c->sp[i]->is_visible)
			continue ;
		c->sp[i]->dy = c->py - c->sp[i]->y;
		c->sp[i]->dx = c->px - c->sp[i]->x;
		c->sp[i]->dist_to_player = \
			sqrt(c->sp[i]->dx * c->sp[i]->dx + c->sp[i]->dy * c->sp[i]->dy);
		if (c->sp[i]->dist_to_player > 0.7)
		{
			current_time = mlx_get_time();
			if (current_time - c->sp[i]->last_frame_time >= 0.15)
			{
				update_squirrel_position(c, c->sp[i]);
				update_squirrel_texture_frame(c->sp[i]);
				c->sp[i]->last_frame_time = current_time;
			}
			get_squirrel_size_and_pos(c, c->sp[i]);
		}
	}
}
