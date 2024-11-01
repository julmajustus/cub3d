/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:56:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/01 20:57:19 by jmakkone         ###   ########.fr       */
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

int	rotate_view_keyboard(t_caster *c)
{
	int retval;

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
	c->plane_x = -0.66 * sin(c->view_angle);
	c->plane_y = 0.66 * cos(c->view_angle);
	return (retval);
}
