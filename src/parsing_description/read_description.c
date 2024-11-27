/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:00:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/27 16:47:39 by skwon2           ###   ########.fr       */
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

static void	check_each_line(t_caster *c, char **line)
{
	int	line_check;
	int	count_gnl;

	count_gnl = 0;
	line_check = 0;
	while (*line)
	{
		if (count_gnl > INT_MAX - 100)
			exit_failure(c, "Over the limit of height of map.");
		if (whole_space_line(*line))
		{
			if (line_check >= end && c->map->map_arr && c->map->map_arr[0])
				exit_failure(c, "Newline in between the map.");
			if (*line)
				free_and_null((void **)line);
			*line = get_next_line(c->map->map_fd);
			count_gnl++;
			continue ;
		}
		process_line(c, line, &line_check);
		if (*line)
			free_and_null((void **)line);
		*line = get_next_line(c->map->map_fd);
		count_gnl++;
	}
}

void	check_map(t_caster *c)
{
	char	*line;

	line = get_next_line(c->map->map_fd);
	if (!line)
		exit_failure(c, "Empty description.");
	check_each_line(c, &line);
}

void	read_description(t_caster *c)
{
	c->textures->north_texture = NULL;
	c->textures->south_texture = NULL;
	c->textures->west_texture = NULL;
	c->textures->east_texture = NULL;
	file_exist(c, c->map->map_path, ".cub", MAP);
	check_map(c);
	print_map(c);
	find_player_pos(c);
	check_wall(c);
	print_map(c);
}
