/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:20:13 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/17 22:16:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void apply_glow_effect(t_caster *c)
{
	int y;
	int x;
	int thick;
	int index;

	y = 0;
	thick = 3;
	while (y < (int)c->wall_texture->height)
	{
		x = 0;
		while (x < (int)c->wall_texture->width)
		{
			index = (y * (int)c->wall_texture->width + x) * 4;

			if ( x <= thick || x >= (int)c->wall_texture->width - thick \
			|| y <= thick || y >= (int)c->wall_texture->height - thick)
			{
				c->wall_texture->pixels[index] = 255;
				c->wall_texture->pixels[index + 1] = 0;
				c->wall_texture->pixels[index + 2] = 0;
				c->wall_texture->pixels[index + 3] = 255;
			}
			x++;
		}
		y++;
	}
}

void	get_wall_texture(t_caster *c)
{
	if (c->map->map_arr[c->map_y][c->map_x] == 'D')
	{
		c->wall_texture = c->textures->door_texture;
		return ;
	}
	if (c->map->map_arr[c->map_y][c->map_x] == 'X')
	{
		c->wall_texture = c->textures->exit;
		apply_glow_effect(c);
		return;
	}
	if (c->wall_hit_is_horizontal == 0)
	{
		if (c->ray_dir_x > 0)
			c->wall_texture = c->textures->east_texture;
		else
			c->wall_texture = c->textures->west_texture;
	}
	else
	{
		if (c->ray_dir_y > 0)
			c->wall_texture = c->textures->south_texture;
		else
			c->wall_texture = c->textures->north_texture;
	}
}

void	get_texture_offset(t_caster *c)
{
	double	wall_texture_offset;

	if (c->wall_hit_is_horizontal == 0)
		wall_texture_offset = c->py + c->wall_dist * c->ray_dir_y;
	else
		wall_texture_offset = c->px + c->wall_dist * c->ray_dir_x;
	wall_texture_offset -= (int)(wall_texture_offset);
	c->tex_x = (int)(wall_texture_offset * (double)TEXTURE_WIDTH);
}
