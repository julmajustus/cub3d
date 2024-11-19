/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_view_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:57:17 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 10:32:23 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	get_fc_tex_index(t_caster *c, int x)
{
	c->rays[x].tex_x = ((int)(c->fc_x * TEXTURE_WIDTH)) & (TEXTURE_WIDTH - 1);
	c->rays[x].tex_y = ((int)(c->fc_y * TEXTURE_HEIGHT)) & (TEXTURE_HEIGHT - 1);
	if (c->rays[x].tex_x < 0)
		c->rays[x].tex_x += TEXTURE_WIDTH;
	if (c->rays[x].tex_y < 0)
		c->rays[x].tex_y += TEXTURE_HEIGHT;
	c->rays[x].tex_index = (c->rays[x].tex_y * TEXTURE_WIDTH + c->rays[x].tex_x) * 4;
}

static void	get_ceiling_colors(t_caster *c, int x, int *y)
{
	uint32_t	color;

	*y = 0;
	while (*y < c->rays[x].draw_start)
	{
		if (FC_TEXTURES)
		{
			c->fc_base_x = c->px + c->fc_row_dist_buffer[*y] * c->cos_table[0];
			c->fc_base_y = c->py + c->fc_row_dist_buffer[*y] * c->sin_table[0];
			c->fc_x = c->fc_base_x + x \
				* c->fc_step_x * c->fc_row_dist_buffer[*y];
			c->fc_y = c->fc_base_y + x \
				* c->fc_step_y * c->fc_row_dist_buffer[*y];
			get_fc_tex_index(c, x);
			color = (c->textures->c_texture->pixels[c->rays[x].tex_index] << 24) \
			| (c->textures->c_texture->pixels[c->rays[x].tex_index + 1] << 16) \
			| (c->textures->c_texture->pixels[c->rays[x].tex_index + 2] << 8) \
			| c->textures->c_texture->pixels[c->rays[x].tex_index + 3];
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
	int			pixel_pos;
	int			tex_index;

	while (*y < c->rays[x].draw_end)
	{
		get_wall_texture(c, x);
		c->rays[x].tex_x = (int)(c->rays[x].wall_texture_offset * TEXTURE_WIDTH);
		pixel_pos = (*y - (-c->rays[x].wall_height / 2 + HEIGHT / 2));
		c->rays[x].tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->rays[x].wall_height);
		tex_index = (c->rays[x].tex_y * TEXTURE_WIDTH + c->rays[x].tex_x) * 4;
		color = (c->rays[x].wall_texture->pixels[tex_index] << 24) \
			| (c->rays[x].wall_texture->pixels[tex_index + 1] << 16) \
			| (c->rays[x].wall_texture->pixels[tex_index + 2] << 8) \
			| c->rays[x].wall_texture->pixels[tex_index + 3];
		c->view_buffer[*y * WIDTH + x] = color;
		(*y)++;
	}
}

static void	get_floor_colors(t_caster *c, int x, int *y)
{
	uint32_t	color;

	*y = c->rays[x].draw_end;
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
			get_fc_tex_index(c, x);
			color = (c->textures->f_texture->pixels[c->rays[x].tex_index] << 24) \
			| (c->textures->f_texture->pixels[c->rays[x].tex_index + 1] << 16) \
			| (c->textures->f_texture->pixels[c->rays[x].tex_index + 2] << 8) \
			| c->textures->f_texture->pixels[c->rays[x].tex_index + 3];
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
		if (c->rays[x].hit_is_horizontal == 0)
			c->rays[x].wall_texture_offset = c->py + \
				c->rays[x].wall_dist * c->sin_table[x];
		else
			c->rays[x].wall_texture_offset = c->px + \
				c->rays[x].wall_dist * c->cos_table[x];
		c->rays[x].wall_texture_offset -= \
			(int)(c->rays[x].wall_texture_offset);
	}
	x = -1;
	while (++x < WIDTH)
	{
		get_ceiling_colors(c, x, &y);
		get_wall_colors(c, x, &y);
		get_floor_colors(c, x, &y);
	}
}
