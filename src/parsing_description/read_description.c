/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/10/31 17:58:12 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void print_map(t_caster *c)
{
	for (int y = 0; y < c->map->map_width; y++)
	{
		for (int x = 0; x < c->map->map_width; x++)
		{
			printf("%d", c->map->map_arr[y][x]);
		}
		printf("\n");
	}
}

void	read_description(t_caster *c)
{
	file_exist(c, c->map->map_path, ".cub", MAP);
	check_map(c);
	printf("hello\n");
	c->map->scale_x = (double)((WIDTH / 5) / c->map->map_width);
	c->map->scale_y = (double)((HEIGHT / 5) / c->map->map_height);
	print_map(c);
	find_player_pos(c);
	check_wall(c);
}



