/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pixel_color_buffers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:30:10 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 05:02:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	get_texture_pixel_colors(t_caster *c, int **buf, mlx_texture_t *tex)
{
	int	i;
	int	j;
	int	buffer_len;

	buffer_len = tex->height * tex->width;
	*buf = malloc(sizeof(int) * buffer_len);
	if (!buf)
		exit_failure(c, "Pixel color buffer malloc failed.");
	i = -1;
	j = 0;
	while (++i < buffer_len)
	{
		(*buf)[i] = (tex->pixels[j] << 24) \
			| (tex->pixels[j + 1] << 16) \
			| (tex->pixels[j + 2] << 8) \
			| tex->pixels[j + 3];
		j += 4;
	}
}

void	init_pixel_color_buffers(t_caster *c)
{
	get_texture_pixel_colors(c, &c->no_wall_pixel_buffer, \
						c->textures->north_texture);
	get_texture_pixel_colors(c, &c->so_wall_pixel_buffer, \
						c->textures->south_texture);
	get_texture_pixel_colors(c, &c->we_wall_pixel_buffer, \
						c->textures->west_texture);
	get_texture_pixel_colors(c, &c->ea_wall_pixel_buffer, \
						c->textures->east_texture);
	get_texture_pixel_colors(c, &c->door_pixel_buffer, \
						c->textures->door_texture);
	get_texture_pixel_colors(c, &c->exit_pixel_buffer, c->textures->exit);
	get_texture_pixel_colors(c, &c->ceiling_pixel_buffer, \
						c->textures->c_texture);
	get_texture_pixel_colors(c, &c->floor_pixel_buffer, c->textures->f_texture);
	get_texture_pixel_colors(c, &c->sp_pixel_buffer, c->textures->sp_texture);
}
