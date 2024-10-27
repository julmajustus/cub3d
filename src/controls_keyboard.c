/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:18:06 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/23 20:59:21 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_collision(t_caster *c, double new_px, double new_py)
{
    double collision_radius = 0.25;
    int collision_x = 0, collision_y = 0;

    if (c->map->map_arr[(int)c->py][(int)(new_px - collision_radius)] == '1' ||
        c->map->map_arr[(int)c->py][(int)(new_px + collision_radius)] == '1')
    {
        collision_x = 1;
    }
    if (c->map->map_arr[(int)(new_py - collision_radius)][(int)c->px] == '1' ||
        c->map->map_arr[(int)(new_py + collision_radius)][(int)c->px] == '1')
    {
		collision_y = 1;
	}
//	if (c->map->map_arr[(int)(new_py - collision_radius)][(int)(new_px - collision_radius)] == '1' ||
//		c->map->map_arr[(int)(new_py - collision_radius)][(int)(new_px + collision_radius)] == '1' ||
//		c->map->map_arr[(int)(new_py + collision_radius)][(int)(new_px - collision_radius)] == '1' ||
//		c->map->map_arr[(int)(new_py + collision_radius)][(int)(new_px + collision_radius)] == '1')
	if (collision_x && collision_y)
		return 0;  // Block movement completely
	if (!collision_x)
		c->px = new_px;
	if (!collision_y)
		c->py = new_py;
    c->mmap_px = c->px * c->map->scale_x;
    c->mmap_py = c->py * c->map->scale_y;
    return (!collision_x || !collision_y);
}

int	movement_up_down(t_caster *c)
{
	double new_px;
	double new_py;

	if (mlx_is_key_down(c->img->handle, MLX_KEY_W))
	{
		new_px = c->px + cos(c->view_angle) * c->speed_multiplier * 1.4;
		new_py = c->py + sin(c->view_angle) * c->speed_multiplier * 1.4;
		return (check_collision(c, new_px, new_py));
	}
	else if (mlx_is_key_down(c->img->handle, MLX_KEY_S))
	{
		new_px = c->px - cos(c->view_angle) * c->speed_multiplier;
		new_py = c->py - sin(c->view_angle) * c->speed_multiplier;
		return (check_collision(c, new_px, new_py));
	}
	return (0);
}

int	movement_left_right(t_caster *c)
{
	double new_px;
	double new_py;

	if (mlx_is_key_down(c->img->handle, MLX_KEY_A))
	{
		new_px = c->px + sin(c->view_angle) * c->speed_multiplier;
		new_py = c->py - cos(c->view_angle) * c->speed_multiplier;
		return (check_collision(c, new_px, new_py));
	}
	else if (mlx_is_key_down(c->img->handle, MLX_KEY_D))
	{
		new_px = c->px - sin(c->view_angle) * c->speed_multiplier;
		new_py = c->py + cos(c->view_angle) * c->speed_multiplier;
		return (check_collision(c, new_px, new_py));
	}
	return (0);
}

int	turn_left_right(t_caster *c)
{
	int retval;

	retval = 0;
	if (mlx_is_key_down(c->img->handle, MLX_KEY_LEFT))
	{
		c->view_angle -= c->speed_multiplier;
		if (c->view_angle < -M_PI)
			c->view_angle += 2 * M_PI;
		retval = 1;
	}
	else if (mlx_is_key_down(c->img->handle, MLX_KEY_RIGHT))
	{
		c->view_angle += c->speed_multiplier;
		if (c->view_angle > M_PI)
			c->view_angle -= 2 * M_PI;
		retval = 1;
	}
	c->plane_x = -0.66 * sin(c->view_angle);
	c->plane_y = 0.66 * cos(c->view_angle);
	return (retval);
}

static void	keys_utils(mlx_key_data_t key, t_caster *c)
{
	if (key.key == MLX_KEY_ESCAPE)
	{
		exit_mlx(c);
		return ;
	}
	else if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
		;
	else if (key.key == MLX_KEY_R && key.action == MLX_PRESS)
		;
}

int	check_movement(t_caster *c)
{
	if (movement_up_down(c))
		return (1);
	if (movement_left_right(c))
		return (1);
	if (turn_left_right(c))
		return (1);
	return (0);
}

void	keyboard_listener(mlx_key_data_t key, void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	keys_utils(key, c);
}
