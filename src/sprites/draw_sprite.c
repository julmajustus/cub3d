/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:11:20 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 04:12:01 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_draw_limits(t_caster *c, t_sprite *sp, int y, int x)
{
	if (sp->screen_x + x >= 0 && sp->screen_x + x < WIDTH \
		&& sp->screen_y + y >= 0 && sp->screen_y + y < HEIGHT \
		&& sp->cam_y < c->wall_dist[sp->screen_x + x])
		return (1);
	return (0);
}

void	draw_sprite(t_caster *c, t_sprite *sp, int size)
{
	int		y;
	int		x;

	y = -1;
	while (++y < size)
	{
		sp->tex_y = (int)(y * TEXTURE_WIDTH / size);
		x = -1;
		while (++x < size)
		{
			sp->tex_x = (int)(x * TEXTURE_WIDTH / size);
			sp->tex_index = sp->frame_offset \
				+ sp->tex_y * 64 + sp->tex_x;
			sp->color = c->sp_pixel_buffer[sp->tex_index];
			if (sp->color == 0)
				continue ;
			if (check_draw_limits(c, sp, y, x))
				mlx_put_pixel(c->window->view, \
					sp->screen_x + x, sp->screen_y + y, sp->color);
		}
	}
}
