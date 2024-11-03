/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/03 01:38:44 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void print_map(t_caster *c)
{
	int y = 0;
	while (y < c->map->map_height && c->map->map_arr[y])
	{
		int x = 0;
		while (x < c->map->map_width && c->map->map_arr[y][x])
		{
			printf("%c", c->map->map_arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	read_description(t_caster *c)
{
	file_exist(c, c->map->map_path, ".cub", MAP);
	check_map(c);
	c->map->scale_x = (double)((WIDTH / 5) / c->map->map_width);
	c->map->scale_y = (double)((HEIGHT / 5) / c->map->map_height);
	print_map(c);
	find_player_pos(c);
	check_wall(c);
	printf("helllllllllllllllll\n");
	print_map(c);
}



