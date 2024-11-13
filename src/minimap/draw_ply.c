/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:56:20 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/13 19:04:09 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_player_in_middle(t_caster *c)
{
	c->mmap->cam_x = (int)(c->px * c->map->scale_x) - PLAYER_CENTER;
	c->mmap->cam_y = (int)(c->py * c->map->scale_y) - PLAYER_CENTER;
	if (c->map->map_width * c->map->scale_x < MINIMAP_SIZE)
		c->mmap->cam_x = (c->map->map_width \
			* c->map->scale_x - MINIMAP_SIZE) / 2;
	else if (c->mmap->cam_x > (c->map->map_width \
			* c->map->scale_x) - MINIMAP_SIZE)
		c->mmap->cam_x = (c->map->map_width \
			* c->map->scale_x) - MINIMAP_SIZE;
	if (c->map->map_height * c->map->scale_y < MINIMAP_SIZE)
		c->mmap->cam_y = (c->map->map_height \
			* c->map->scale_y - MINIMAP_SIZE) / 2;
	else if (c->mmap->cam_y > (c->map->map_height \
			* c->map->scale_y) - MINIMAP_SIZE)
		c->mmap->cam_y = (c->map->map_height \
			* c->map->scale_y) - MINIMAP_SIZE;
}

void	draw_pixel(t_caster *c, int x, int y, int color)
{
	if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
	{
		mlx_put_pixel(c->window->minimap, x, y, color);
	}
}

void	draw_ray(t_caster *c, int player_x, int player_y)
{
	int		i;

	i = -1;
	while (++i < 66)
	{
		c->mmap->ray_x = player_x;
		c->mmap->ray_y = player_y;
		while (c->mmap->ray_x >= 0 && c->mmap->ray_x < MINIMAP_SIZE \
			&& c->mmap->ray_y >= 0 && c->mmap->ray_y < MINIMAP_SIZE)
		{
			c->mmap->map_x = (int)((c->mmap->ray_x + c->mmap->cam_x) \
				/ c->map->scale_x);
			c->mmap->map_y = (int)((c->mmap->ray_y + c->mmap->cam_y) \
				/ c->map->scale_y);
			if (c->mmap->map_y < 0 || c->mmap->map_y >= c->map->map_height \
				|| c->mmap->map_x < 0 || c->mmap->map_x >= c->map->map_width \
				|| c->map->map_arr[c->mmap->map_y][c->mmap->map_x] == '1')
				break ;
			draw_pixel(c, (int)(c->mmap->ray_x + 2.5), \
				(int)(c->mmap->ray_y + 2.5), 0xFF0000FF);
			c->mmap->ray_x += cos(c->mmap->ray_angle) * c->mmap->ray_len;
			c->mmap->ray_y += sin(c->mmap->ray_angle) * c->mmap->ray_len;
		}
		c->mmap->ray_angle += c->plane_x / 100.0;
	}
}

void	draw_player(t_caster *c)
{
	int	player_x;
	int	player_y;

	player_x = c->mmap_px - c->mmap->cam_x;
	player_y = c->mmap_py - c->mmap->cam_y;
	restrict_sizes_to_mimmap(&player_x, &player_y);
	printf("player_x : %d\n player_y : %d\n", player_x, player_y);
	c->mmap->ray_len = 0.1;
	c->mmap->ray_angle = c->view_angle - (c->plane_x / 2);
	draw_ray(c, player_x, player_y);
	draw_tiles(c, player_x, player_y, 2);
}
