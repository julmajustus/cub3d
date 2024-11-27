/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_texture_buffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:16:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 04:57:12 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	*get_wall_texture_buffer(t_caster *c, int x)
{
	if (c->hit_surface[x] == 'D')
	{
		return (c->door_pixel_buffer);
	}
	else if (c->hit_surface[x] == 'X')
	{
		return (c->exit_pixel_buffer);
	}
	else if (c->hit_is_horizontal[x] == 0)
	{
		if (c->cos_table[x] > 0)
			return (c->ea_wall_pixel_buffer);
		else
			return (c->we_wall_pixel_buffer);
	}
	else
	{
		if (c->sin_table[x] > 0)
			return (c->so_wall_pixel_buffer);
		else
			return (c->no_wall_pixel_buffer);
	}
}
