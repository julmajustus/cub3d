/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:03:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 04:59:18 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	precalculate_wall_texture_offset(t_caster *c)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		if (c->hit_is_horizontal[x] == 0)
			c->wall_texture_offset_buffer[x] = c->py + \
				c->wall_dist[x] * c->sin_table[x];
		else
			c->wall_texture_offset_buffer[x] = c->px + \
				c->wall_dist[x] * c->cos_table[x];
		c->wall_texture_offset_buffer[x] -= \
			(int)(c->wall_texture_offset_buffer[x]);
	}
}

static void	render_wall(t_caster *c, int x, int y)
{
	uint32_t	color;
	int			*pixel_buffer;
	int			pixel_pos;

	pixel_buffer = get_wall_texture_buffer(c, x);
	c->tex_x = (int)(c->wall_texture_offset_buffer[x] * TEXTURE_WIDTH);
	while (y < c->draw_end[x])
	{
		pixel_pos = (y - (-c->wall_height[x] / 2 + HEIGHT / 2));
		c->tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->wall_height[x]);
		color = pixel_buffer[c->tex_y * TEXTURE_WIDTH + c->tex_x];
		mlx_put_pixel(c->window->view, x, y, color);
		y++;
	}
}

void	render_view(t_caster *c)
{
	int		x;

	precalculate_wall_texture_offset(c);
	c->fc_step_x = (c->cos_table[WIDTH - 1] - c->cos_table[0]) / WIDTH;
	c->fc_step_y = (c->sin_table[WIDTH - 1] - c->sin_table[0]) / WIDTH;
	x = -1;
	while (++x < WIDTH)
	{
		render_wall(c, x, c->draw_start[x]);
		if (FC_TEXTURES)
			render_fc_textures(c, c->draw_end[x], x);
		else
			render_fc_plain_colors(c, c->draw_end[x], x);
	}
}
