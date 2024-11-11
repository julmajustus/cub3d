/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:05:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/12 01:08:15 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void init_sprites(t_caster *c)
{
    mlx_texture_t *texture = mlx_load_png("./textures/squirrel.png");
    if (!texture)
        exit_failure(c, "Failed to load sprite texture");
    c->squirrel = malloc(sizeof(t_sprite));
    if (!c->squirrel)
        exit_failure(c, "Failed to allocate memory for sprite");
    c->squirrel->sprite_texture = texture;
    c->squirrel->frame_count = 5;
    c->squirrel->current_frame = 0;
    c->squirrel->last_frame_time = 0.0;
    c->squirrel->x = 25.0;
    c->squirrel->y = 3.0;
	c->squirrel->is_visible = 0;
}

void update_sprite_frame(t_sprite *sprite)
{
	if (sprite->current_frame == 1)
		sprite->x += 0.2;
	else if (sprite->current_frame == 2)
		sprite->y -= 0.2;
	else if (sprite->current_frame == 3)
		sprite->x -= 0.2;
	else if (sprite->current_frame == 4)
		sprite->y += 0.2;
    sprite->current_frame = (sprite->current_frame + 1) % sprite->frame_count;
}

void draw_sprite_pixel(t_caster *c, int screen_x, int screen_y, int sprite_size)
{
	int	y;
	int	x;
    int frame_offset = c->squirrel->current_frame * 64 * 64 * 4;
    double step = 64.0 / sprite_size;

	y = -1;
    while (++y < sprite_size)
	{
        int tex_y = (int)(y * step);
		x = -1;
        while (++x < sprite_size)
		{
            int tex_x = (int)(x * step);
            int tex_index = frame_offset + (tex_y * 64 + tex_x) * 4;

            c->squirrel->color = (c->squirrel->sprite_texture->pixels[tex_index] << 24) |
                             (c->squirrel->sprite_texture->pixels[tex_index + 1] << 16) |
                             (c->squirrel->sprite_texture->pixels[tex_index + 2] << 8) |
                             c->squirrel->sprite_texture->pixels[tex_index + 3];

            if ((c->squirrel->color >> 24) == 0) continue;

            int screen_pixel_x = screen_x + x;
            int screen_pixel_y = screen_y + y;

            if (screen_pixel_x >= 0 && screen_pixel_x < WIDTH &&
                screen_pixel_y >= 0 && screen_pixel_y < HEIGHT) {
                mlx_put_pixel(c->window->view, screen_x + x, screen_y + y, c->squirrel->color);
            }
        }
    }
}

void draw_sprite(t_caster *c, t_sprite *sprite)
{
	//if (!sprite->is_visible)
      //  return ;
	sprite->is_visible = 0;
    // Step 1: Sprite position relative to the player
    double dx = sprite->x - c->px;
    double dy = sprite->y - c->py;

    // Step 2: Convert sprite position to camera coordinates
    double inv_det = 1.0 / (c->plane_x * sin(c->view_angle) - cos(c->view_angle) * c->plane_y);
    double transform_x = inv_det * (sin(c->view_angle) * dx - cos(c->view_angle) * dy);
    double transform_y = inv_det * (-c->plane_y * dx + c->plane_x * dy);

    // If sprite is in front of the camera
    if (transform_y > 0)
	{
        // Step 3: Calculate sprite position on screen (X-coordinate)
        int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
        // Step 4: Scale the sprite based on distance (adjust with Z-depth)
        int sprite_height = (int)fabs(HEIGHT / (transform_y * 2));
        // Step 5: Calculate the start of the sprite's Y-position (relative to the camera)
        int draw_start_y = (HEIGHT / 2) + (sprite_height / 2);
        // Step 6: Adjust for perspective and draw the sprite correctly on the floor
        draw_start_y += sprite_height / 4;  // Adjust to make it appear closer to the ground
		printf("Check draw_start_y : %d sprite_height: %d\n", draw_start_y, sprite_height);
       	draw_sprite_pixel(c, sprite_screen_x - sprite_height / 2, draw_start_y, sprite_height);
    }
}

void render_sprites(t_caster *c)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - c->squirrel->last_frame_time >= 0.15)
	{
    	update_sprite_frame(c->squirrel);
		c->squirrel->last_frame_time = current_time;
	}
   	draw_sprite(c, c->squirrel);
}
