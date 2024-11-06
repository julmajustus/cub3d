/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/06 21:32:03 by skwon2           ###   ########.fr       */
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
	// c->map->scale_x = (double)((WIDTH / 6) / c->map->map_width);
	// c->map->scale_y = (double)((HEIGHT / 6) / c->map->map_height);
	// // 예시: scale_x를 미니맵 크기와 맵 크기에 맞게 조정
	// c->map->scale_x = (double)MINIMAP_WIDTH / c->map->map_width;
	// c->map->scale_y = (double)MINIMAP_HEIGHT / c->map->map_height;

	print_map(c);
	find_player_pos(c);
	check_wall(c);
	print_map(c);
}



