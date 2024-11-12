/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:56:20 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/12 01:57:57 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_player_to_minimap(t_caster *c)
{
    // draw_minimap(c, c->mmap_px, c->mmap_py, 3);
    printf("Player pos X: %f Y: %f\n", c->mmap_px, c->mmap_py);
    printf("speed_multiplier: %f\n", c->speed_multiplier);
}

void put_player_in_middle(t_caster *c)
{
    c->mmap->camera_offset_x = (int)(c->px * c->map->scale_x) - PLAYER_CENTER;
    c->mmap->camera_offset_y = (int)(c->py * c->map->scale_y) - PLAYER_CENTER;
    // contraints for offset value to fit inside of Minimap
    // the map is smaller size than the size fo min_window
    if (c->map->map_width * c->map->scale_x < MINIMAP_SIZE)
        c->mmap->camera_offset_x = (c->map->map_width * c->map->scale_x - MINIMAP_SIZE) / 2;
    else if (c->mmap->camera_offset_x > (c->map->map_width * c->map->scale_x) - MINIMAP_SIZE)
        c->mmap->camera_offset_x = (c->map->map_width * c->map->scale_x) - MINIMAP_SIZE;
    if (c->map->map_height * c->map->scale_y < MINIMAP_SIZE)
        c->mmap->camera_offset_y = (c->map->map_height * c->map->scale_y - MINIMAP_SIZE) / 2;
    else if (c->mmap->camera_offset_y > (c->map->map_height * c->map->scale_y) - MINIMAP_SIZE)
        c->mmap->camera_offset_y = (c->map->map_height * c->map->scale_y) - MINIMAP_SIZE;
}

void draw_pixel(t_caster *c, int x, int y, int color)
{
    if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
    {
        mlx_put_pixel(c->window->minimap, x, y, color);
    }
}

void draw_ray(t_caster *c, int player_x, int player_y)
{
    double ray_len = 0.1;
    double ray_angle = c->view_angle - (c->plane_x / 2);
    double ray_x, ray_y;
    int i;

    i = -1;
    while (++i < 66)
    {
        ray_x = player_x;
        ray_y = player_y;
        while (ray_x >= 0 && ray_x < MINIMAP_SIZE && ray_y >= 0 && ray_y < MINIMAP_SIZE)
        {
            int map_x = (int)((ray_x + c->mmap->camera_offset_x) / c->map->scale_x);
            int map_y = (int)((ray_y + c->mmap->camera_offset_y) / c->map->scale_y);
            if (c->map->map_arr[map_y][map_x] == '1')
                break;
            draw_pixel(c, (int)(ray_x + 2.5), (int)(ray_y + 2.5), 0xFF000080);
            ray_x += cos(ray_angle) * ray_len;
            ray_y += sin(ray_angle) * ray_len;
        }
        ray_angle += c->plane_x / 100.0;
    }
}

void draw_player(t_caster *c)
{
    int player_x;
    int player_y;

    player_x = c->mmap_px - c->mmap->camera_offset_x;
    player_y = c->mmap_py - c->mmap->camera_offset_y;
    restrict_sizes_to_mimmap(&player_x, &player_y);
    printf("player_x : %d\n player_y : %d\n", player_x, player_y);
    draw_ray(c, player_x, player_y);
    draw_tiles(c, player_x, player_y, 2);
}

