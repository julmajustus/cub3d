/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kill_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:50:00 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/24 23:45:28 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_player_death_count(t_caster *c)
{
	char	*death_count;
	char	*str;

	death_count = safe_itoa(c, c->death_count);
	str = safe_strjoin(c, "PLAYER DEATH COUNT: ", death_count);
	free(death_count);
	if (c->window->death_count)
		mlx_delete_image(c->window->handle, c->window->death_count);
	c->window->death_count = mlx_put_string(c->window->handle, \
										str, 750, 720);
	mlx_resize_image(c->window->death_count, 400, 70);
	c->window->death_count->instances[0].z = 5;
	free(str);
}

void	draw_highest_kill_count(t_caster *c)
{
	char	*kill_count;
	char	*str;

	if (c->kill_count > c->highest_kill_count)
	{
		c->highest_kill_count = c->kill_count;
		kill_count = safe_itoa(c, c->highest_kill_count);
	}
	else
		kill_count = safe_itoa(c, c->highest_kill_count);
	str = safe_strjoin(c, "HIGHEST KILL COUNT: ", kill_count);
	free(kill_count);
	if (c->window->highest_kill_count)
		mlx_delete_image(c->window->handle, c->window->highest_kill_count);
	c->window->highest_kill_count = mlx_put_string(c->window->handle, \
										str, 750, 650);
	mlx_resize_image(c->window->highest_kill_count, 400, 70);
	c->window->highest_kill_count->instances[0].z = 5;
	free(str);
}

void	draw_kill_count(t_caster *c)
{
	char	*kill_count;
	char	*str;

	kill_count = safe_itoa(c, c->kill_count);
	str = safe_strjoin(c, "KILL COUNT: ", kill_count);
	free(kill_count);
	if (c->window->kill_count)
		mlx_delete_image(c->window->handle, c->window->kill_count);
	c->window->kill_count = mlx_put_string(c->window->handle, \
										str, WIDTH - 400, 20);
	mlx_resize_image(c->window->kill_count, 300, 70);
	c->window->kill_count->instances[0].z = 3;
	free(str);
}
