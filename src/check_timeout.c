/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_timeout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:47:20 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/19 16:14:28 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_timeout(t_caster *c)
{
	if (c->start_time.tv_sec == 0 && c->start_time.tv_usec == 0)
		gettimeofday(&c->start_time, NULL);
	gettimeofday(&c->current_time, NULL);
	c->elapsed_time = (c->current_time.tv_sec - c->start_time.tv_sec) \
	+ (c->current_time.tv_usec - c->start_time.tv_usec) / 1000000.0;
	if (c->elapsed_time > TIMEOUT)
	{
		c->game_status = -1;
		if (c->time_text_img)
			mlx_delete_image(c->window->handle, c->time_text_img);
	}
}

void	draw_elapsed_time(t_caster *c)
{
	double		left_time;
	char		*int_part;
	char		*decimal_part;
	char		*new_time;
	char		*leftover_time;

	if (c->elapsed_time <= TIMEOUT)
	{
		if (c->time_text_img)
			mlx_delete_image(c->window->handle, c->time_text_img);
		left_time = TIMEOUT - c->elapsed_time;
		int_part = ft_itoa((int)(left_time));
		decimal_part = ft_itoa((int)((left_time - (int)(left_time)) * 1000));
		leftover_time = ft_strjoin(int_part, ".");
		new_time = ft_strjoin(leftover_time, decimal_part);
		free(leftover_time);
		leftover_time = ft_strjoin("TIME : ", new_time);
		free(new_time);
		c->time_text_img = mlx_put_string(c->window->handle, \
		leftover_time, (WIDTH / 2) - 10, (2 / HEIGHT) + 20);
		free(leftover_time);
		free(int_part);
		free(decimal_part);
	}
}
