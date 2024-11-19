/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:11:26 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 22:58:50 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render_fc_plain_colors(t_caster *c, int draw_end, int x)
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

static int	get_fc_tex_index(t_caster *c)
{
	int	tex_x;
	int	tex_y;

	tex_x = (int)(c->fc_x * TEXTURE_WIDTH) % TEXTURE_WIDTH;
	tex_y = (int)(c->fc_y * TEXTURE_HEIGHT) % TEXTURE_HEIGHT;
	if (tex_x < 0)
		tex_x += TEXTURE_WIDTH;
	if (tex_y < 0)
		tex_y += TEXTURE_HEIGHT;
	return ((tex_y * TEXTURE_WIDTH + tex_x) * 4);
}

static void	render_ceiling(t_caster *c, int *y_ceiling, int x, int index)
{
	uint8_t		*p_buf;
	uint32_t	color;

	p_buf = c->textures->c_texture->pixels;
	color = (p_buf[index] << 24) \
		| (p_buf[index + 1] << 16) \
		| (p_buf[index + 2] << 8) \
		| p_buf[index + 3];
	mlx_put_pixel(c->window->view, x, (*y_ceiling)--, color);
}

static void	render_floor(t_caster *c, int *y_floor, int x, int index)
{
	uint8_t		*p_buf;
	uint32_t	color;

	p_buf = c->textures->f_texture->pixels;
	color = (p_buf[index] << 24) \
		| (p_buf[index + 1] << 16) \
		| (p_buf[index + 2] << 8) \
		| p_buf[index + 3];
	mlx_put_pixel(c->window->view, x, (*y_floor)++, color);
}

void	render_fc_textures(t_caster *c, int draw_end, int x)
{
	int		tex_index;
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
		tex_index = get_fc_tex_index(c);
		if (y_floor < HEIGHT)
			render_floor(c, &y_floor, x, tex_index);
		if (y_ceiling >= 0)
			render_ceiling(c, &y_ceiling, x, tex_index);
	}
}
