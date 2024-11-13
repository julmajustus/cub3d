/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:00:01 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/13 13:42:09 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_pixels(t_caster *c, int x, int y, int ratio)
{
    int i;
    int j;
    mlx_image_t *window;

    window = c->window->minimap;
    i = -1;
    while (++i < c->map->scale_y / ratio)
    {
        j = -1;
        while (++j < c->map->scale_x / ratio)
        {
            if (x + j < (int)window->width && y + i < (int)window->height)
                mlx_put_pixel(window, x + j, y + i, c->mmap->color);
        }
    }
}

uint32_t mlx_get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
    int index;

    if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
        return 0;
    index = (y * texture->width + x) * 4;
    uint8_t r = texture->pixels[index];
    uint8_t g = texture->pixels[index + 1];
    uint8_t b = texture->pixels[index + 2];
    uint8_t a = texture->pixels[index + 3];

    return (r << 24) | (g << 16) | (b << 8) | a;
}

void draw_scaled_img_to_tile(t_caster *c, int x, int y, mlx_texture_t *img)
{
    int i;
    int j;
    uint32_t color;

    i = -1;
    while (++i < c->map->scale_y)
    {
        j = -1;
        while (++j < c->map->scale_x)
        {
            if (x + j < (int)c->window->minimap->width && y + i < (int)c->window->minimap->height)
            {
                color = mlx_get_texture_pixel(img, (i * img->width) / c->map->scale_y, (j * img->height) / c->map->scale_x);
                mlx_put_pixel(c->window->minimap, x + j, y + i, color);
            }
        }
    }
}

void draw_tiles(t_caster *c, int x, int y, int flag)
{
    mlx_texture_t *img;

    img = NULL;
    if (flag == 1)
        img = c->mmap->wall;
    if (flag == 0)
        img = c->mmap->space;
    if (flag == 2)
    {
        c->mmap->color = 0x000000FF;
        draw_pixels(c, x, y, 2);
        return;
    }
    if (flag == 3)
        img = c->mmap->door;
    if (img)
        draw_scaled_img_to_tile(c, x, y, img);
}

void find_which_tiles(t_caster *c, int x, int y)
{
    int minimap_x;
    int minimap_y;

    minimap_x = (int)(x * c->map->scale_x) - c->mmap->camera_offset_x;
    minimap_y = (int)(y * c->map->scale_y) - c->mmap->camera_offset_y;
    restrict_sizes_to_mimmap(&minimap_x, &minimap_x);
    if (c->map->map_arr[y][x] == '1')
        draw_tiles(c, minimap_x, minimap_y, 1);
    else if (c->map->map_arr[y][x] == '0')
        draw_tiles(c, minimap_x, minimap_y, 0);
    else if (c->map->map_arr[y][x] == 'D')
    {
        if (is_door_open(c, y, x))
            draw_tiles(c, minimap_x, minimap_y, 0);
        else if (!is_door_open(c, y, x))
            draw_tiles(c, minimap_x, minimap_y, 3);
    }
}


