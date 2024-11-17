/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:33:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/18 00:59:05 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_texture(t_caster *c, mlx_texture_t **texture)
{
	if (c->game_status == 0)
		*texture = c->textures->press_Enter;
	else if (c->game_status == 1)
		*texture = c->textures->press_menu_enter;
	else if (c->game_status == -1 || c->game_status == -2)
		*texture = c->textures->press_R;
	else
		return (1);
	return (0);
}

static void blink_text(t_caster *c)
{
	static struct timeval	last_blink_time;
	struct timeval			current_time;
	long					elapsed_time;
	mlx_texture_t			*texture;

	if (check_texture(c, &texture) == 1)
		return;
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_blink_time.tv_sec) * 1000 + \
	(current_time.tv_usec - last_blink_time.tv_usec) / 1000;
	if (c->blink_state == 0 && elapsed_time > 200)
	{
		c->blink_state = 1;
		gettimeofday(&last_blink_time, NULL);
	}
	else if (c->blink_state == 1 && elapsed_time > 600)
	{
		c->blink_state = 0;
		gettimeofday(&last_blink_time, NULL);
	}
	draw_text(c, texture, c->blink_state);
}

void check_game_status(t_caster *c)
{
	if (c->game_status == 0)
	{
		draw_scene(c, c->textures->start_screen, HEIGHT, WIDTH);
		blink_text(c);
	}
	else if (c->game_status == 1)
	{
		draw_scene(c, c->textures->menu_screen, HEIGHT, WIDTH);
		blink_text(c);
	}
	else if (c->game_status == -1 || c->game_status == -2)
	{
		c->py = c->map->spawn_location_y;
		c->px = c->map->spawn_location_x;
		set_images_to_window(c);
		c->active_sprite_count = 1;
		if (c->game_status == -1)
			draw_scene(c, c->textures->death_screen, HEIGHT, WIDTH);
		if (c->game_status == -2)
			draw_scene(c, c->textures->succeed_screen, HEIGHT, WIDTH);
		blink_text(c);
	}
}
