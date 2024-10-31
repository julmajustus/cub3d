/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:54:48 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/30 15:22:58 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	calculate_ray_angle_and_casting_position(t_caster *c)
{
	c->ray_dir_x = cos(c->view_angle) + c->plane_x * c->camera;
	c->ray_dir_y = sin(c->view_angle) + c->plane_y * c->camera;
	c->delta_dist_x = fabs(1 / c->ray_dir_x);
	c->delta_dist_y = fabs(1 / c->ray_dir_y);
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (c->px - c->map_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - c->px) * c->delta_dist_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (c->py - c->map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - c->py) * c->delta_dist_y;
	}
}

static void	find_ray_hit_position_and_side(t_caster *c)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (c->side_dist_x < c->side_dist_y)
		{
			c->side_dist_x += c->delta_dist_x;
			c->map_x += c->step_x;
			c->wall_hit_side = 0;
		}
		else
		{
			c->side_dist_y += c->delta_dist_y;
			c->map_y += c->step_y;
			c->wall_hit_side = 1;
		}
		if (c->map_x >= c->map->map_width || c->map_y >= c->map->map_height)
			break ;
		if (c->map->map_arr[c->map_y][c->map_x] == '1')
			hit = 1;
	}
}

static void	calculate_wall_distance_and_height(t_caster *c)
{
	if (c->wall_hit_side == 0)
		c->wall_dist = (c->map_x - c->px + (1 - c->step_x) / 2) / c->ray_dir_x;
	else
		c->wall_dist = (c->map_y - c->py + (1 - c->step_y) / 2) / c->ray_dir_y;
	c->wall_height = (int)(HEIGHT / c->wall_dist);
	c->draw_start = -c->wall_height / 2 + HEIGHT / 2;
	if (c->draw_start < 0)
		c->draw_start = 0;
	c->draw_end = c->wall_height / 2 + HEIGHT / 2;
	if (c->draw_end >= HEIGHT)
		c->draw_end = HEIGHT - 1;
}

static void	get_texture_for_wall_direction(t_caster *c)
{
	if (c->wall_hit_side == 0)
	{
		if (c->ray_dir_x > 0)
			c->wall_texture = c->textures->east_texture;
		else
			c->wall_texture = c->textures->west_texture;
	}
	else
	{
		if (c->ray_dir_y > 0)
			c->wall_texture = c->textures->south_texture;
		else
			c->wall_texture = c->textures->north_texture;
	}
}

static void	calculate_x_cordinate_for_wall_stripe(t_caster *c)
{
	double	wall_hit_pos_x;

	if (c->wall_hit_side == 0)
		wall_hit_pos_x = c->py + c->wall_dist * c->ray_dir_y;
	else
		wall_hit_pos_x = c->px + c->wall_dist * c->ray_dir_x;
	wall_hit_pos_x -= floor(wall_hit_pos_x);
	c->tex_x = (int)(wall_hit_pos_x * (double)TEXTURE_WIDTH);
}

static void	draw_wall_stripe(t_caster *c, int x)
{
	int	y;
	int	pixel_pos;
	int	tex_index;

	y = c->draw_start;
	while (y <= c->draw_end)
	{
		pixel_pos = (y - (-c->wall_height / 2 + HEIGHT / 2));
		c->tex_y = ((pixel_pos * TEXTURE_HEIGHT) / c->wall_height);
		if (c->tex_y >= TEXTURE_HEIGHT)
			c->tex_y = TEXTURE_HEIGHT - 1;
		if (c->tex_y < 0)
			c->tex_y = 0;
		tex_index = (c->tex_y * TEXTURE_WIDTH + c->tex_x) * 4;
		c->pixel_color = (c->wall_texture->pixels[tex_index] << 24) \
			| (c->wall_texture->pixels[tex_index + 1] << 16) \
			| (c->wall_texture->pixels[tex_index + 2] << 8) \
			| c->wall_texture->pixels[tex_index + 3];
		mlx_put_pixel(c->img->view, x, y, c->pixel_color);
		y++;
	}
}

static void	draw_floor_and_ceiling_for_stripe(t_caster *c, int draw_end, int x)
{
	int			y;

	y = draw_end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(c->img->view, x, y, c->textures->floor_color);
		mlx_put_pixel(c->img->view, x, HEIGHT - y - 1, c->textures->ceiling_color);
		y++;
	}
}

void	raycaster(t_caster *c)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		c->camera = 2 * x / (double)WIDTH - 1;
		c->map_x = (int)c->px;
		c->map_y = (int)c->py;
		calculate_ray_angle_and_casting_position(c);
		find_ray_hit_position_and_side(c);
		calculate_wall_distance_and_height(c);
		get_texture_for_wall_direction(c);
		calculate_x_cordinate_for_wall_stripe(c);
		draw_wall_stripe(c, x);
		draw_floor_and_ceiling_for_stripe(c, c->draw_end, x);
	}
}
