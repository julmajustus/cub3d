/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:18:06 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 04:56:58 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	movement_up_down(t_caster *c)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(c->window->handle, MLX_KEY_W))
	{
		new_px = c->px + cos(c->view_angle) * c->speed_multiplier * 1.4;
		new_py = c->py + sin(c->view_angle) * c->speed_multiplier * 1.4;
		return (check_collision(c, new_px, new_py));
	}
	else if (mlx_is_key_down(c->window->handle, MLX_KEY_S))
	{
		new_px = c->px - cos(c->view_angle) * c->speed_multiplier;
		new_py = c->py - sin(c->view_angle) * c->speed_multiplier;
		return (check_collision(c, new_px, new_py));
	}
	return (0);
}

int	movement_left_right(t_caster *c)
{
	double	new_px;
	double	new_py;

	if (mlx_is_key_down(c->window->handle, MLX_KEY_A))
	{
		new_px = c->px + sin(c->view_angle) * c->speed_multiplier;
		new_py = c->py - cos(c->view_angle) * c->speed_multiplier;
		return (check_collision(c, new_px, new_py));
	}
	else if (mlx_is_key_down(c->window->handle, MLX_KEY_D))
	{
		new_px = c->px - sin(c->view_angle) * c->speed_multiplier;
		new_py = c->py + cos(c->view_angle) * c->speed_multiplier;
		return (check_collision(c, new_px, new_py));
	}
	return (0);
}

static void	game_controls(mlx_key_data_t key, t_caster *c)
{
	if (key.key == MLX_KEY_ESCAPE)
	{
		exit_mlx(c);
		return ;
	}
	else if (!BONUS)
		return ;
	else if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS \
		&& c->game_status == 2)
	{
		start_gun_fire_animation(c->gun);
		check_sprite_hit(c);
	}
	else if (key.key == MLX_KEY_F && key.action == MLX_PRESS \
		&& c->game_status == 2)
	{
		toggle_door(c, ACTION_DISTANCE);
	}
}

static void	menu_controls(mlx_key_data_t key, t_caster *c)
{
	if (key.key == MLX_KEY_ENTER && key.action == MLX_PRESS)
	{
		if (c->game_status == 0 || c->game_status == 1)
		{
			c->game_status += 1;
			if (c->game_status == 2 && BONUS)
				render_gun(c);
		}
	}
	else if (key.key == MLX_KEY_R && key.action == MLX_PRESS)
	{
		if (c->game_status == -1 || c->game_status == -2)
		{
			if (c->window->highest_kill_count)
				mlx_delete_image(c->window->handle, \
					c->window->highest_kill_count);
			if (c->window->death_count)
				mlx_delete_image(c->window->handle, c->window->death_count);
			c->death_count++;
			c->game_status = 2;
			render_gun(c);
		}
	}
}

void	keyboard_listener(mlx_key_data_t key, void *param)
{
	t_caster	*c;

	c = (t_caster *)param;
	game_controls(key, c);
	menu_controls(key, c);
}
