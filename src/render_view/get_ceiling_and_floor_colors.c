/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling_and_floor_colors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:11:26 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 19:54:15 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_fc_plain_colors(t_caster *c, int draw_end, int x)
{
	int	y_floor;
	int	y_ceiling;

	y_floor = draw_end;
	y_ceiling = HEIGHT - draw_end - 1;
	while (y_floor < HEIGHT && y_ceiling >= 0)
	{
		c->view_buffer[y_ceiling-- * WIDTH + x] = c->textures->ceiling_color;
		c->view_buffer[y_floor++ * WIDTH + x] = c->textures->floor_color;
	}
}

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

static void	render_ceiling(t_caster *c, int *y_ceiling, int x)
{
	c->pixel_color = (c->textures->c_texture->pixels[c->tex_index] << 24) \
		| (c->textures->c_texture->pixels[c->tex_index + 1] << 16) \
		| (c->textures->c_texture->pixels[c->tex_index + 2] << 8) \
		| c->textures->c_texture->pixels[c->tex_index + 3];
	mlx_put_pixel(c->window->view, x, (*y_ceiling)--, c->pixel_color);
	//c->view_buffer[(*y_ceiling)-- * WIDTH + x] = c->pixel_color;
}

static void	render_floor(t_caster *c, int *y_floor, int x)
{
	c->pixel_color = (c->textures->f_texture->pixels[c->tex_index] << 24) \
		| (c->textures->f_texture->pixels[c->tex_index + 1] << 16) \
		| (c->textures->f_texture->pixels[c->tex_index + 2] << 8) \
		| c->textures->f_texture->pixels[c->tex_index + 3];
	mlx_put_pixel(c->window->view, x, (*y_floor)++, c->pixel_color);
	//c->view_buffer[(*y_floor)++ * WIDTH + x] = c->pixel_color;
}

void	fill_fc_texture_colors(t_caster *c, int draw_end, int x)
{
	int		y_floor;
	int		y_ceiling;

	y_floor = draw_end;
	y_ceiling = HEIGHT - draw_end - 1;
	c->fc_step_x = (c->cos_table[WIDTH - 1] - c->cos_table[0]) / WIDTH;
	c->fc_step_y = (c->sin_table[WIDTH - 1] - c->sin_table[0]) / WIDTH;
	while (y_floor < HEIGHT || y_ceiling >= 0)
	{
		c->fc_base_x = c->px + c->fc_row_dist_buffer[y_floor] * c->cos_table[0];
		c->fc_base_y = c->py + c->fc_row_dist_buffer[y_floor] * c->sin_table[0];
		c->fc_x = c->fc_base_x + x \
			* c->fc_step_x * c->fc_row_dist_buffer[y_floor];
		c->fc_y = c->fc_base_y + x \
			* c->fc_step_y * c->fc_row_dist_buffer[y_floor];
		get_fc_tex_index(c);
		if (y_floor < HEIGHT)
			render_floor(c, &y_floor, x);
		if (y_ceiling >= 0)
			render_ceiling(c, &y_ceiling, x);
	}
}
