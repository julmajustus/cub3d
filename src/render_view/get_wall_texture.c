/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:20:13 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/19 10:35:25 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_wall_texture(t_caster *c, int x)
{
	if (c->rays[x].hit_surface == 'D')
	{
		c->rays[x].wall_texture = c->textures->door_texture;
		return ;
	}
	if (c->rays[x].hit_surface == 'X')
	{
		c->rays[x].wall_texture = c->textures->exit;
		return ;
	}
	if (c->rays[x].hit_is_horizontal == 0)
	{
		if (c->cos_table[x] > 0)
			c->rays[x].wall_texture = c->textures->east_texture;
		else
			c->rays[x].wall_texture = c->textures->west_texture;
	}
	else
	{
		if (c->sin_table[x] > 0)
			c->rays[x].wall_texture = c->textures->south_texture;
		else
			c->rays[x].wall_texture = c->textures->north_texture;
	}
}
