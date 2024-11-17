/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:16:47 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/17 22:18:12 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void hit_check(t_caster *c, int *hit)
{
	is_sprite_visible(c, c->map_y, c->map_x);
	if (c->map->map_arr[c->map_y][c->map_x] == 'D' && !is_door_open(c, c->map_y, c->map_x))
		*hit = 1;
	else if (c->map->map_arr[c->map_y][c->map_x] == 'X')
		*hit = 1;
	else if (c->map->map_arr[c->map_y][c->map_x] == '1')
		*hit = 1;
}

void	trace_ray_until_wall_hit(t_caster *c)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (c->dist_to_grid_x < c->dist_to_grid_y)
		{
			c->dist_to_grid_x += c->dist_increment_x;
			c->map_x += c->step_x;
			c->wall_hit_is_horizontal = 0;
		}
		else
		{
			c->dist_to_grid_y += c->dist_increment_y;
			c->map_y += c->step_y;
			c->wall_hit_is_horizontal = 1;
		}
		hit_check(c, &hit);
	}
}

void	render_wall_column(t_caster *c, int x)
{
	int	y;
	int	pixel_pos;
	int	tex_index;

	y = c->draw_start;
	while (y < c->draw_end)
	{
		pixel_pos = (y - (-c->wall_height / 2 + HEIGHT / 2));
		c->tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->wall_height);
		if (c->tex_y >= TEXTURE_HEIGHT)
			c->tex_y = TEXTURE_HEIGHT - 1;
		if (c->tex_y < 0)
			c->tex_y = 0;
		tex_index = (c->tex_y * TEXTURE_WIDTH + c->tex_x) * 4;
		c->pixel_color = (c->wall_texture->pixels[tex_index] << 24) \
			| (c->wall_texture->pixels[tex_index + 1] << 16) \
			| (c->wall_texture->pixels[tex_index + 2] << 8) \
			| c->wall_texture->pixels[tex_index + 3];
		if (y > 0 && y < HEIGHT)
			mlx_put_pixel(c->window->view, x, y, c->pixel_color);
		y++;
	}
}
