/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:20:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/18 15:12:51 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_player_direction(t_caster *c, size_t x, size_t y)
{
	if (c->map->map_arr[y][x] == 'N')
		c->view_angle = -M_PI_2;
	else if (c->map->map_arr[y][x] == 'S')
		c->view_angle = M_PI_2;
	else if (c->map->map_arr[y][x] == 'E')
		c->view_angle = 0;
	else if (c->map->map_arr[y][x] == 'W')
		c->view_angle = M_PI;
}

static void	check_else_char(t_caster *c, char character)
{
	if (BONUS)
	{
		if (ft_strchr("01D NSWEX", character) == NULL)
			exit_failure(c, "Invalid characters in the map.");
	}
	else
	{
		if (ft_strchr("01 NSWE", character) == NULL)
			exit_failure(c, "Invalid characters in the map.");
	}
}

static void	store_position_player(t_caster *c, int *found, size_t x, size_t y)
{
	if (c->map->map_arr[y][x] == 'N' || c->map->map_arr[y][x] == 'S' ||
		c->map->map_arr[y][x] == 'W' || c->map->map_arr[y][x] == 'E')
	{
		(*found)++;
		c->px = x + 0.50;
		c->py = y + 0.50;
		c->mmap_px = x * MINIMAP_SCALE;
		c->mmap_py = y * MINIMAP_SCALE;
		c->map->spawn_location_x = c->px;
		c->map->spawn_location_y = c->py;
		set_player_direction(c, x, y);
	}
}

void	check_condition(t_caster *c, int found, int exit)
{
	if (BONUS && exit == 0)
		exit_failure(c, "Exit not found.");
	if (found == 0)
		exit_failure(c, "Player not found.");
	else if (found > 1)
		exit_failure(c, "There is more than one player.");
}

void	find_player_pos(t_caster *c)
{
	size_t	x;
	size_t	y;
	int		exit;
	int		found;

	found = 0;
	y = -1;
	exit = 0;
	while (++y < (size_t)c->map->map_height)
	{
		x = -1;
		while (++x < ft_strlen(c->map->map_arr[y]))
		{
			if (c->map->map_arr[y][x] == 'X')
				exit = 1;
			check_else_char(c, c->map->map_arr[y][x]);
			store_position_player(c, &found, x, y);
		}
	}
	check_condition(c, found, exit);
}
