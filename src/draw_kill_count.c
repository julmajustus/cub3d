/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kill_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:50:00 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/22 16:09:22 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_kill_count(t_caster *c)
{

	char *str;

	str = ft_itoa(c->kill_count);
		if (c->window->kill_count)
			mlx_delete_image(c->window->handle, c->window->kill_count);
		c->window->kill_count = mlx_put_string(c->window->handle, \
		str, (WIDTH / 2) - 10, (2 / HEIGHT) + 50);
	free(str);
}
