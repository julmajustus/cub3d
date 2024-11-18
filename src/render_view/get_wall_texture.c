/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:20:13 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/18 23:15:32 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_wall_texture(t_caster *c, int x)
{
	if (c->hit_surface[x] == 'D')
	{
		c->wall_texture = c->textures->door_texture;
		return ;
	}
	if (c->hit_surface[x] == 'X')
	{
		c->wall_texture = c->textures->exit;
		return ;
	}
	if (c->hit_is_horizontal[x] == 0)
	{
		if (c->cos_table[x] > 0)
			c->wall_texture = c->textures->east_texture;
		else
			c->wall_texture = c->textures->west_texture;
	}
	else
	{
		if (c->sin_table[x] > 0)
			c->wall_texture = c->textures->south_texture;
		else
			c->wall_texture = c->textures->north_texture;
	}
}
