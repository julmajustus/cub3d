/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:18:06 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/01 20:02:31 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_collision(t_caster *c, double new_px, double new_py)
{
    int		can_move_x = 1;
    int		can_move_y = 1;
	double	dir_x;
	double	dir_y;

   dir_x = cos(c->view_angle) * 0.15;
   dir_y = sin(c->view_angle) * 0.15;
	if (c->map->map_arr[(int)(new_py)][(int)(new_px)] != '0')
		return (0);
    if (c->map->map_arr[(int)c->py][(int)(new_px + dir_x)] == '1' ||
        c->map->map_arr[(int)c->py][(int)(new_px - dir_x)] == '1')
        can_move_x = 0;
    if (c->map->map_arr[(int)(new_py + dir_y)][(int)c->px] == '1' ||
        c->map->map_arr[(int)(new_py - dir_y)][(int)c->px] == '1')
        can_move_y = 0;
    if (can_move_x)
        c->px = new_px;
    if (can_move_y)
        c->py = new_py;
    c->mmap_px = c->px * c->map->scale_x;
    c->mmap_py = c->py * c->map->scale_y;
    return (can_move_x || can_move_y);
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

void	check_cursor_movement(t_caster *c)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(c->img->handle, &x, &y);
	c->cursor_pos = WIDTH / 2 - x;
	mlx_set_mouse_pos(c->img->handle, WIDTH / 2, HEIGHT / 2);
}

int	rotate_view_keyboard(t_caster *c)
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

int	rotate_view_mouse(t_caster *c)
{
	int retval;

	retval = 0;
	if (c->cursor_pos > 0)
	{
		c->view_angle -= 1.1 * c->speed_multiplier;
		if (c->view_angle < -M_PI)
			c->view_angle += 2 * M_PI;
		retval = 1;
		c->plane_x = -0.66 * sin(c->view_angle);
		c->plane_y = 0.66 * cos(c->view_angle);
	}
	else if (c->cursor_pos < 0)
	{
		c->view_angle += 1.1 * c->speed_multiplier;
		if (c->view_angle < M_PI)
			c->view_angle -= 2 * M_PI;
		retval = 1;
		c->plane_x = -0.66 * sin(c->view_angle);
		c->plane_y = 0.66 * cos(c->view_angle);
	}
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

void	keyboard_listener(mlx_key_data_t key, void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	keys_utils(key, c);
}
