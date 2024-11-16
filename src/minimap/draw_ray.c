/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:46:08 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/16 11:32:06 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_pixel(t_caster *c, int x, int y, int color)
{
	if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
	{
		mlx_put_pixel(c->window->minimap, x, y, color);
	}
}

void	draw_one_ray(t_caster *c)
{
	while (c->mmap->ray_x >= 0 && c->mmap->ray_x < MINIMAP_SIZE && \
	c->mmap->ray_y >= 0 && c->mmap->ray_y < MINIMAP_SIZE)
	{
		c->mmap->map_x = (int)((c->mmap->ray_x + c->mmap->cam_x) \
		/ c->map->scale_x);
		c->mmap->map_y = (int)((c->mmap->ray_y + c->mmap->cam_y) \
		/ c->map->scale_y);
		if (c->mmap->map_y < 0 \
		|| c->mmap->map_y >= c->map->map_height - 1 \
		|| c->mmap->map_x < 0 \
		|| c->mmap->map_x >= c->map_row_len_buffer[c->mmap->map_y] \
		|| c->map->map_arr[c->mmap->map_y][c->mmap->map_x] == '1' \
		|| (c->map->map_arr[c->mmap->map_y][c->mmap->map_x] == 'D' \
		&& !is_door_open(c, c->mmap->map_y, c->mmap->map_x)))
			break ;
		draw_pixel(c, (int)(c->mmap->ray_x + 2.5), \
		(int)(c->mmap->ray_y + 2.5), 0xFF0000FF);
		c->mmap->ray_x += cos(c->mmap->ray_angle) * c->mmap->ray_len;
		c->mmap->ray_y += sin(c->mmap->ray_angle) * c->mmap->ray_len;
	}
}

void	draw_ray(t_caster *c, int player_x, int player_y)
{
	int		i;
	float	fov;
	float	ray_step;

	fov = 66 * (M_PI / 180);
	ray_step = fov / 66;
	c->mmap->ray_angle = c->view_angle - (fov / 2);
	i = -1;
	while (++i < 66)
	{
		c->mmap->ray_x = player_x;
		c->mmap->ray_y = player_y;
		draw_one_ray(c);
		c->mmap->ray_angle += ray_step;
		c->mmap->ray_angle = fmod(c->mmap->ray_angle, 2 * M_PI);
		if (c->mmap->ray_angle < 0)
			c->mmap->ray_angle += 2 * M_PI;
	}
}
