/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:20:13 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/17 04:59:48 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_wall_texture(t_caster *c)
{
	if (c->map->map_arr[c->map_y][c->map_x] == 'D')
	{
		c->wall_texture = c->textures->door_texture;
		return ;
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
