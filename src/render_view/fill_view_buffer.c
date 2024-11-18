/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_view_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:57:17 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/18 23:14:55 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	get_fc_tex_index(t_caster *c)
{
	c->tex_x = (int)(c->fc_x * TEXTURE_WIDTH) % TEXTURE_WIDTH;
	c->tex_y = (int)(c->fc_y * TEXTURE_HEIGHT) % TEXTURE_HEIGHT;
	if (c->tex_x < 0)
		c->tex_x += TEXTURE_WIDTH;
	if (c->tex_y < 0)
		c->tex_y += TEXTURE_HEIGHT;
	c->tex_index = (c->tex_y * TEXTURE_WIDTH + c->tex_x) * 4;
}

static void	get_ceiling_colors(t_caster *c, int x, int *y)
{
	uint32_t	color;

	while (*y < c->draw_start[x])
	{
		if (BONUS)
		{
			c->fc_base_x = c->px + c->fc_row_dist_buffer[*y] * c->cos_table[0];
			c->fc_base_y = c->py + c->fc_row_dist_buffer[*y] * c->sin_table[0];
			c->fc_x = c->fc_base_x + x \
				* c->fc_step_x * c->fc_row_dist_buffer[*y];
			c->fc_y = c->fc_base_y + x \
				* c->fc_step_y * c->fc_row_dist_buffer[*y];
			get_fc_tex_index(c);
			color = (c->textures->c_texture->pixels[c->tex_index] << 24) \
			| (c->textures->c_texture->pixels[c->tex_index + 1] << 16) \
			| (c->textures->c_texture->pixels[c->tex_index + 2] << 8) \
			| c->textures->c_texture->pixels[c->tex_index + 3];
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
	double		wall_texture_offset;
	int			pixel_pos;
	int			tex_index;

	while (*y < c->draw_end[x])
	{
		get_wall_texture(c, x);
		if (c->hit_is_horizontal[x] == 0)
			wall_texture_offset = c->py + c->wall_dist[x] * c->sin_table[x];
		else
			wall_texture_offset = c->px + c->wall_dist[x] * c->cos_table[x];
		wall_texture_offset -= (int)(wall_texture_offset);
		c->tex_x = (int)(wall_texture_offset * TEXTURE_WIDTH);
		pixel_pos = (*y - (-c->wall_height[x] / 2 + HEIGHT / 2));
		c->tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->wall_height[x]);
		tex_index = (c->tex_y * TEXTURE_WIDTH + c->tex_x) * 4;
		color = (c->wall_texture->pixels[tex_index] << 24) \
		| (c->wall_texture->pixels[tex_index + 1] << 16) \
		| (c->wall_texture->pixels[tex_index + 2] << 8) \
		| c->wall_texture->pixels[tex_index + 3];
		c->view_buffer[*y * WIDTH + x] = color;
		(*y)++;
	}
}

static void	get_floor_colors(t_caster *c, int x, int *y)
{
	uint32_t	color;

	while (*y < HEIGHT)
	{
		if (BONUS)
		{
			c->fc_base_x = c->px + c->fc_row_dist_buffer[*y] * c->cos_table[0];
			c->fc_base_y = c->py + c->fc_row_dist_buffer[*y] * c->sin_table[0];
			c->fc_x = c->fc_base_x + x \
				* c->fc_step_x * c->fc_row_dist_buffer[*y];
			c->fc_y = c->fc_base_y + x \
				* c->fc_step_y * c->fc_row_dist_buffer[*y];
			get_fc_tex_index(c);
			color = (c->textures->f_texture->pixels[c->tex_index] << 24) \
			| (c->textures->f_texture->pixels[c->tex_index + 1] << 16) \
			| (c->textures->f_texture->pixels[c->tex_index + 2] << 8) \
			| c->textures->f_texture->pixels[c->tex_index + 3];
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
		y = 0;
		get_ceiling_colors(c, x, &y);
		y = c->draw_start[x];
		get_wall_colors(c, x, &y);
		y = c->draw_end[x];
		get_floor_colors(c, x, &y);
	}
}
