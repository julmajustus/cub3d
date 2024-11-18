/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:53:13 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/18 15:16:58 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_scene(t_caster *c, mlx_texture_t *texture, int height, int width)
{
	t_scene	scene;

	scene.y = -1;
	while (++scene.y < height)
	{
		scene.x = -1;
		while (++scene.x < width)
		{
			scene.offset = (scene.y * width + scene.x) * 4;
			if (texture->pixels[scene.offset + 3] == 0)
				continue ;
			scene.color = (texture->pixels[scene.offset] << 24) \
			| (texture->pixels[scene.offset + 1] << 16) \
			| (texture->pixels[scene.offset + 2] << 8) \
			| texture->pixels[scene.offset + 3];
			mlx_put_pixel(c->window->view, scene.x, scene.y, scene.color);
		}
	}
}

void	text_draw(t_caster *c, mlx_texture_t *texture, t_scene *scene)
{
	while (++scene->y < (int)texture->height)
	{
		scene->x = -1;
		while (++scene->x < (int)texture->width)
		{
			scene->offset = (scene->y * texture->width + scene->x) * 4;
			if (texture->pixels[scene->offset + 3] == 0)
				continue ;
			scene->color = (texture->pixels[scene->offset] << 24) \
			| (texture->pixels[scene->offset + 1] << 16) \
			| (texture->pixels[scene->offset + 2] << 8) \
			| texture->pixels[scene->offset + 3];
			mlx_put_pixel(c->window->view, scene->spot_x + scene->x, \
			scene->spot_y + scene->y, scene->color);
		}
	}
}

void	draw_text(t_caster *c, mlx_texture_t *texture, int blink)
{
	t_scene	scene;

	if (c->game_status == 1)
	{
		scene.spot_x = (WIDTH / 2) - (texture->width / 2);
		scene.spot_y = ((HEIGHT / 3) * 2 + 230);
	}
	else
	{
		scene.spot_x = (WIDTH / 2) - (texture->width / 2);
		scene.spot_y = ((HEIGHT / 3) * 2 + 100);
	}
	if (blink == 0)
		return ;
	scene.y = -1;
	text_draw(c, texture, &scene);
}
