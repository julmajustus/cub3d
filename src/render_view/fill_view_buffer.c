/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_view_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:57:17 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 16:48:45 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	get_fc_tex_index(t_caster *c)
{
	int tex_x;
	int tex_y;


	tex_x = ((int)(c->fc_x * TEXTURE_WIDTH)) & (TEXTURE_WIDTH - 1);
	tex_y = ((int)(c->fc_y * TEXTURE_HEIGHT)) & (TEXTURE_HEIGHT - 1);
	if (tex_x < 0)
		tex_x += TEXTURE_WIDTH;
	if (tex_y < 0)
		tex_y += TEXTURE_HEIGHT;
	return ((tex_y * TEXTURE_WIDTH + tex_x) * 4);
}

static void	get_ceiling_colors(t_caster *c, int x, int *y)
{
	uint8_t		*pixels;
	int		i;
	uint32_t	color;

	*y = 0;
	pixels = c->textures->c_texture->pixels;
	while (*y < c->draw_start[x])
	{
		if (FC_TEXTURES)
		{
			c->fc_base_x = c->px + c->fc_row_dist_buffer[*y] * c->cos_table[0];
			c->fc_base_y = c->py + c->fc_row_dist_buffer[*y] * c->sin_table[0];
			c->fc_x = c->fc_base_x + x \
				* c->fc_step_x * c->fc_row_dist_buffer[*y];
			c->fc_y = c->fc_base_y + x \
				* c->fc_step_y * c->fc_row_dist_buffer[*y];
			i = get_fc_tex_index(c);
			color = (pixels[i] << 24) | (pixels[i + 1] << 16) \
			| (pixels[i + 2] << 8) | pixels[i + 3];
		}
		else
			color = c->textures->ceiling_color;
		c->view_buffer[*y * WIDTH + x] = color;
		(*y)++;
	}
}

static void	get_wall_colors(t_caster *c, int x, int *y)
{
	uint32_t	color;
	uint8_t		*pixels;
	int		pixel_pos;
	int		i;

	get_wall_texture(c, x);
	pixels = c->wall_texture->pixels;
	while (*y < c->draw_end[x])
	{
		c->tex_x = (int)(c->wall_texture_offset_buffer[x] * TEXTURE_WIDTH);
		pixel_pos = (*y - (-c->wall_height[x] / 2 + HEIGHT / 2));
		c->tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->wall_height[x]);
		i = (c->tex_y * TEXTURE_WIDTH + c->tex_x) * 4;
		color = (pixels[i] << 24) \
			| (pixels[i + 1] << 16) \
			| (pixels[i + 2] << 8) \
			| pixels[i + 3];
		c->view_buffer[*y * WIDTH + x] = color;
		(*y)++;
	}
}

static void	get_floor_colors(t_caster *c, int x, int *y)
{
	uint8_t		*pixels;
	int		i;
	uint32_t	color;

	pixels = c->textures->f_texture->pixels;
	*y = c->draw_end[x];
	while (*y < HEIGHT)
	{
		if (FC_TEXTURES)
		{
			c->fc_base_x = c->px + c->fc_row_dist_buffer[*y] * c->cos_table[0];
			c->fc_base_y = c->py + c->fc_row_dist_buffer[*y] * c->sin_table[0];
			c->fc_x = c->fc_base_x + x \
				* c->fc_step_x * c->fc_row_dist_buffer[*y];
			c->fc_y = c->fc_base_y + x \
				* c->fc_step_y * c->fc_row_dist_buffer[*y];
			i = get_fc_tex_index(c);
			color = (pixels[i] << 24) | (pixels[i + 1] << 16) \
				| (pixels[i + 2] << 8) | pixels[i + 3];
		}
		else
			color = c->textures->floor_color;
		c->view_buffer[*y * WIDTH + x] = color;
		(*y)++;
	}
}

void	fill_view_buffer(t_caster *c)
{
	int		x;
	int		y;

	c->fc_step_x = (c->cos_table[WIDTH - 1] - c->cos_table[0]) / WIDTH;
	c->fc_step_y = (c->sin_table[WIDTH - 1] - c->sin_table[0]) / WIDTH;
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
	x = -1;
	while (++x < WIDTH)
	{
		get_ceiling_colors(c, x, &y);
		get_wall_colors(c, x, &y);
		get_floor_colors(c, x, &y);
	}
}
