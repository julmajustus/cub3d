/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_timeout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:47:20 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/16 13:11:38 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void check_timeout(t_caster *c)
{
	static struct timeval	start_time;
	struct timeval			current_time;

	if (c->game_status == 0)
	{
		start_time.tv_sec = 0;
		start_time.tv_usec = 0;
	}
	if (start_time.tv_sec == 0 && start_time.tv_usec == 0)
		gettimeofday(&start_time, NULL);
	gettimeofday(&current_time, NULL);
	c->elapsed_time = (current_time.tv_sec - start_time.tv_sec) + (current_time.tv_usec - start_time.tv_usec) / 1000000.0;
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
	char	*int_part;
	char	*decimal_part;
	char	*leftover_time;

	if (c->elapsed_time <= TIMEOUT)
	{
		if (c->time_text_img)
			mlx_delete_image(c->window->handle, c->time_text_img);
		left_time = TIMEOUT - c->elapsed_time;
		int_part = ft_itoa((int)(left_time));
		decimal_part = ft_itoa((int)((left_time - (int)(left_time)) * 1000));
		printf("time : %s.%s\n", int_part, decimal_part);
		leftover_time = ft_strjoin(int_part, ".");
		leftover_time = ft_strjoin(leftover_time, decimal_part);
		leftover_time = ft_strjoin("TIME : ", leftover_time);
		c->time_text_img = mlx_put_string(c->window->handle, leftover_time, (WIDTH / 2) - 10, (2 / HEIGHT) + 20);
	}
}