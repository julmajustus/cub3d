/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:02:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 05:06:54 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	update_sprite_position(t_caster *c, t_sprite *sp)
{
	sp->current_frame = (sp->current_frame + 1) % sp->frame_count;
	sp->frame_offset = sp->current_frame * 64 * 64;
	if (sp->dist_to_player > 0)
	{
		sp->dx /= sp->dist_to_player;
		sp->dy /= sp->dist_to_player;
	}
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

static void	get_sprite_size_and_pos(t_caster *c, t_sprite *sp)
{
	sp->is_visible = 0;
	sp->dx = sp->x - c->px;
	sp->dy = sp->y - c->py;
	sp->cam_inv = 1.0 / (c->plane_x * sin(c->view_angle) \
		- cos(c->view_angle) * c->plane_y);
	sp->cam_y = sp->cam_inv * (-c->plane_y * sp->dx + c->plane_x * sp->dy);
	sp->cam_x = sp->cam_inv * (sin(c->view_angle) * sp->dx \
		- cos(c->view_angle) * sp->dy);
	if (sp->cam_y > 0)
	{
		sp->screen_x = (int)((WIDTH / 2) * (1 + sp->cam_x / sp->cam_y));
		sp->scale = (int)fabs(HEIGHT / (sp->cam_y));
		if (sp->scale > HEIGHT)
			sp->scale = HEIGHT;
		sp->screen_y = (HEIGHT / 2) - (sp->scale / 1.7);
		sp->screen_y += sp->scale / 3;
		sp->screen_x = sp->screen_x - sp->scale / 2;
		draw_sprite(c, sp, sp->scale);
	}
}

static void	death_animation(t_caster *c, t_sprite *sp)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - sp->last_frame_time >= 0.12)
	{
		sp->current_frame++;
		sp->frame_offset = sp->current_frame * 64 * 64;
		sp->last_frame_time = current_time;
		if (sp->current_frame >= sp->death_frame_count)
		{
			sp->x = -1;
			sp->y = -1;
			sp->is_hit = 0;
			if (c->active_sprite_count < c->max_sprite_count)
			{
				spawn_sprite(c);
				c->active_sprite_count++;
			}
			return ;
		}
	}
	get_sprite_size_and_pos(c, sp);
}

static void	animation(t_caster *c, t_sprite *sp)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - sp->last_frame_time >= 0.12)
	{
		update_sprite_position(c, sp);
		sp->last_frame_time = current_time;
	}
	get_sprite_size_and_pos(c, sp);
}

void	render_sprites(t_caster *c)
{
	int		i;

	i = -1;
	while (++i < c->active_sprite_count)
	{
		if (!c->sp[i]->is_visible)
			continue ;
		c->sp[i]->dy = c->py - c->sp[i]->y;
		c->sp[i]->dx = c->px - c->sp[i]->x;
		c->sp[i]->dist_to_player = \
			sqrt(c->sp[i]->dx * c->sp[i]->dx + c->sp[i]->dy * c->sp[i]->dy);
		if (c->sp[i]->dist_to_player < 0.5 && !c->sp[i]->is_hit)
			c->game_status = -1;
		if (c->sp[i]->is_hit)
			death_animation(c, c->sp[i]);
		else
			animation(c, c->sp[i]);
	}
}
