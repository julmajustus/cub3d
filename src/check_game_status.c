/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:33:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/15 00:46:08 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	draw_screens(t_caster *c, mlx_texture_t *texture)
{
	int			y;
	int			x;
	int			offset;
	uint32_t	color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			offset = (y * WIDTH + x) * 4;
			color = (texture->pixels[offset] << 24) \
				| (texture->pixels[offset + 1] << 16) \
				| (texture->pixels[offset + 2] << 8) \
				| texture->pixels[offset + 3];
			mlx_put_pixel(c->window->view, x, y, color);
		}
	}
}

void	check_game_status(t_caster *c)
{
	if (c->game_status == 0)
		draw_screens(c, c->textures->menu_screen);
	else if (c->game_status == 1)
		draw_screens(c, c->textures->start_screen);
	else if (c->game_status == -1)
	{
		c->py = c->map->spawn_location_y;
		c->px = c->map->spawn_location_x;
		set_images_to_window(c);
		c->active_sprite_count = 1;
		draw_screens(c, c->textures->death_screen);
	}
}
