/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:24:41 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/17 05:28:04 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	color_floor_and_ceiling(t_caster *c, int draw_end, int x)
{
	int	y_floor;
	int	y_ceiling;

	y_floor = draw_end;
	y_ceiling = HEIGHT - draw_end - 1;
	while (y_floor < HEIGHT && y_ceiling >= 0)
	{
		mlx_put_pixel(c->window->view, x, y_floor++, \
		c->textures->floor_color);
		mlx_put_pixel(c->window->view, x, y_ceiling--, \
		c->textures->ceiling_color);
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
}

static void	render_floor(t_caster *c, int *y_floor, int x)
{
	c->pixel_color = (c->textures->f_texture->pixels[c->tex_index] << 24) \
		| (c->textures->f_texture->pixels[c->tex_index + 1] << 16) \
		| (c->textures->f_texture->pixels[c->tex_index + 2] << 8) \
		| c->textures->f_texture->pixels[c->tex_index + 3];
	mlx_put_pixel(c->window->view, x, (*y_floor)++, c->pixel_color);
}

void	render_floor_and_ceiling(t_caster *c, int draw_end, int x)
{
	int		y_floor;
	int		y_ceiling;
	double	inv_width;

	y_floor = draw_end;
	y_ceiling = HEIGHT - draw_end - 1;
	inv_width = 1.0 / WIDTH;
	while (y_floor < HEIGHT || y_ceiling >= 0)
	{
		if (y_floor < HEIGHT)
			c->fc_row_dist = HEIGHT / (2.0 * y_floor - HEIGHT);
		else
			c->fc_row_dist = HEIGHT / (HEIGHT - 2.0 * y_ceiling);
		c->fc_step_x = c->fc_row_dist \
			* (c->cos_table[WIDTH - 1] - c->cos_table[0]) * inv_width;
		c->fc_step_y = c->fc_row_dist \
			* (c->sin_table[WIDTH - 1] - c->sin_table[0]) * inv_width;
		c->fc_x = c->px + c->fc_row_dist * c->cos_table[0] + x * c->fc_step_x;
		c->fc_y = c->py + c->fc_row_dist * c->sin_table[0] + x * c->fc_step_y;
		get_fc_tex_index(c);
		if (y_floor < HEIGHT)
			render_floor(c, &y_floor, x);
		if (y_ceiling >= 0)
			render_ceiling(c, &y_ceiling, x);
	}
}
