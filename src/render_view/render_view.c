/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:03:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/20 09:57:37 by jmakkone         ###   ########.fr       */
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
	uint8_t		*pixels;
	int			pixel_pos;
	int			i;

	get_wall_texture(c, x);
	pixels = c->wall_texture->pixels;
	while (y < c->draw_end[x])
	{
		c->tex_x = (int)(c->wall_texture_offset_buffer[x] * TEXTURE_WIDTH);
		pixel_pos = (y - (-c->wall_height[x] / 2 + HEIGHT / 2));
		c->tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->wall_height[x]);
		i = (c->tex_y * TEXTURE_WIDTH + c->tex_x) * 4;
		color = (pixels[i] << 24) \
			| (pixels[i + 1] << 16) \
			| (pixels[i + 2] << 8) \
			| pixels[i + 3];
		mlx_put_pixel(c->window->view, x, y, color);
		y++;
	}
}

void	render_view(t_caster *c)
{
	int		x;

	precalculate_wall_texture_offset(c);
	x = 0;
	while (x < WIDTH)
	{
		render_wall(c, x, c->draw_start[x]);
		if (FC_TEXTURES)
			render_fc_textures(c, c->draw_end[x], x);
		else
			render_fc_plain_colors(c, c->draw_end[x], x);
		render_wall(c, x + 1, c->draw_start[x]);
		if (FC_TEXTURES)
			render_fc_textures(c, c->draw_end[x + 1], x + 1);
		else
			render_fc_plain_colors(c, c->draw_end[x + 1], x + 1);
		x += 2;
	}

//	if (FC_TEXTURES)
//	{
//		while (x < WIDTH)
//		{
//			render_wall(c, x, c->draw_start[x]);
//			render_fc_textures(c, c->draw_end[x], x);
//			render_wall(c, x + 1, c->draw_start[x]);
//			render_fc_textures(c, c->draw_end[x + 1], x + 1);
//		//	render_wall(c, x + 2, c->draw_start[x + 2]);
//		//	render_fc_textures(c, c->draw_end[x + 2], x + 2);
//		//	render_wall(c, x + 3, c->draw_start[x + 3]);
//		//	render_fc_textures(c, c->draw_end[x + 3], x + 3);
//		//	render_wall(c, x + 4, c->draw_start[x + 4]);
//		//	render_fc_textures(c, c->draw_end[x + 4], x + 4);
//		//	render_wall(c, x + 5, c->draw_start[x + 5]);
//		//	render_fc_textures(c, c->draw_end[x + 5], x + 5);
//			x += 2;
//		}
//	}
//	else
//	{
//		while (x < WIDTH)
//		{
//			render_wall(c, x, c->draw_start[x]);
//			render_fc_plain_colors(c, c->draw_end[x], x);
//			render_wall(c, x + 1, c->draw_start[x]);
//			render_fc_plain_colors(c, c->draw_end[x], x);
//			x += 2;
//		}
//	}
}
