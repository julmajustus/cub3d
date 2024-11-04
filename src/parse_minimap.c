/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:31 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/04 10:56:29 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_minimap(t_caster *c, size_t x, size_t y, int flag)
{
	int i;
	int j;
	uint32_t color;
	mlx_image_t *window;

	window = c->window->minimap;
	if (flag == 1)
		color = 0x000000FF;
	else if (flag == 3)
	{
		window = c->window->player;
		color = 0x00FF00FF;
	}
	else
		color = 0xFFFFFFFF;
	i = -1;
	while (++i < c->map->scale_y)
	{
		j = -1;
		while (++j < c->map->scale_x)
			mlx_put_pixel(window, x + j, y + i, color);
	}
}

void draw_player_to_minimap(t_caster *c)
{
	draw_minimap(c, c->mmap_px, c->mmap_py, 3);
	printf("Player pos X: %f Y: %f\n", c->mmap_px, c->mmap_py);
	printf("speed_multiplier: %f\n", c->speed_multiplier);
}

void parse_minimap(t_caster *c)
{
	size_t x;
	size_t y;
	size_t xo;
	size_t yo;

	y = -1;
	while (++y < (size_t)c->map->map_height)
	{
		x = -1;
		while (++x < ft_strlen(c->map->map_arr[y]))
		{
			xo = x * c->map->scale_x;
			yo = y * c->map->scale_y;
			if (c->map->map_arr[y][x] == '1')
				draw_minimap(c, xo, yo, 1);
			else if (c->map->map_arr[y][x] == '0')
				draw_minimap(c, xo, yo, 0);
			else if (ft_strchr("NSEW", c->map->map_arr[y][x]))
				draw_minimap(c, xo, yo, 0);
		}
	}
}