/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:56:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/25 00:20:20 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_cursor_movement(t_caster *c)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(c->window->handle, &x, &y);
	c->cursor_pos = WIDTH / 2 - x;
	mlx_set_mouse_pos(c->window->handle, WIDTH / 2, HEIGHT / 2);
}

int	rotate_view_mouse(t_caster *c)
{
	int		retval;
	double	mouse_sensitivity;
	double	scaled_rotation;

	retval = 0;
	mouse_sensitivity = 0.025;
	scaled_rotation = -c->cursor_pos * mouse_sensitivity * c->speed_multiplier;
	if (c->cursor_pos != 0)
	{
		c->view_angle += scaled_rotation;
		if (c->view_angle > -M_PI)
			c->view_angle += 2 * M_PI;
		else if (c->view_angle < M_PI)
			c->view_angle -= 2 * M_PI;
		c->plane_x = -1 * sin(c->view_angle);
		c->plane_y = 1 * cos(c->view_angle);
		retval = 1;
	}
	return (retval);
}

int	rotate_view_keyboard(t_caster *c)
{
	int	retval;

	retval = 0;
	if (mlx_is_key_down(c->window->handle, MLX_KEY_LEFT))
	{
		c->view_angle -= c->speed_multiplier;
		if (c->view_angle < -M_PI)
			c->view_angle += 2 * M_PI;
		retval = 1;
	}
	else if (mlx_is_key_down(c->window->handle, MLX_KEY_RIGHT))
	{
		c->view_angle += c->speed_multiplier;
		if (c->view_angle > M_PI)
			c->view_angle -= 2 * M_PI;
		retval = 1;
	}
	c->plane_x = -1 * sin(c->view_angle);
	c->plane_y = 1 * cos(c->view_angle);
	return (retval);
}
