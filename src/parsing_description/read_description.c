/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/21 17:43:06 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_map(t_caster *c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c->map->map_height && c->map->map_arr[y])
	{
		x = 0;
		while (x < c->map->map_width && c->map->map_arr[y][x])
		{
			printf("%c", c->map->map_arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

int	whole_space_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && !(*str >= 9 && *str <= 13))
			return (false);
		str++;
	}
	return (true);
}

void	read_description(t_caster *c)
{
	file_exist(c, c->map->map_path, ".cub", MAP);
	check_map(c);
	print_map(c);
	find_player_pos(c);
	check_wall(c);
	print_map(c);
}
