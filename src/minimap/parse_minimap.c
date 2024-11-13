/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:31 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/12 02:04:45 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_bgcolor_minmap(t_caster *c)
{
	int i;
	int j;

	i = -1;
	c->map->scale_x = MINIMAP_SCALE;// 1보다 커야댐
	c->map->scale_y = MINIMAP_SCALE;
	mlx_image_t *window = c->window->minimap;
	while (++i < MINIMAP_SIZE)
	{
		j = -1;
		while (++j < MINIMAP_SIZE)
			mlx_put_pixel(window, j, i, 0x8B4513FF);
	}
}

void	restrict_sizes_to_mimmap(int *x, int *y)
{
	if ((*x) < 0)
		(*x) = 0;
	else if ((*x) >= MINIMAP_SIZE)
		(*x) = MINIMAP_SIZE - 1;

	if ((*y) < 0)
		(*y) = 0;
	else if ((*y) >= MINIMAP_SIZE)
		(*y) = MINIMAP_SIZE - 1;
}

void draw_sprites(t_caster *c)
{
	int y;
	int x;

	y = 0;
	while (y < c->map->map_height && c->map->map_arr[y])
	{
		x = 0;
		while (x < c->map->map_width && c->map->map_arr[y][x])
		{
			find_which_tiles(c, x, y);
			x++;
		}
		y++;
	}
}

void parse_minimap(t_caster *c)
{
	draw_bgcolor_minmap(c);
	put_player_in_middle(c);
	draw_sprites(c);
	draw_player(c);
}
