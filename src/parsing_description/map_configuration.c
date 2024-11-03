/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_configuration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:24:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/03 09:10:49 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void parse_texture_color(t_caster *c, char *line, const char *order, T_Dir i)
{
	if (!ft_strncmp(line, order, ft_strlen(order)))
	{
		if (i == F || i == C)
			parse_plain_colors(c, line);
		else
		{
			if (line[3] == '.' && line[4] == '/')
				c->map->texture_path = ft_substr(line, 3, ft_strlen(line) - 4);
			// printf("texture file name : %s\n", c->map->texture_path);
			file_exist(c, c->map->texture_path, ".png", TEXTURE);
			if (i == NT)
				c->textures->north_texture = mlx_load_png(c->map->texture_path);
			if (i == ST)
				c->textures->south_texture = mlx_load_png(c->map->texture_path);
			if (i == WT)
				c->textures->west_texture = mlx_load_png(c->map->texture_path);
			if (i == ET)
				c->textures->east_texture = mlx_load_png(c->map->texture_path);
		}
	}
}

void init_var(T_Dir *i, const char **order)
{
	order[0] = "NO ";
	order[1] = "SO ";
	order[2] = "WE ";
	order[3] = "EA ";
	order[4] = "F ";
	order[5] = "C ";
	*i = NT;
}

int whole_space_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && !(*str >= 9 && *str <= 13))
			return (false);
		str++;
	}
	return (true);
}

void process_line(t_caster *c, char **line, T_Dir *i, const char **order)
{
	char *new_line;
	int width;

	width = ft_strlen(*line);
	// printf("width : %d\n", width);
	// printf("Processing *line: %s", *line);
	if (width > c->map->map_width)
		c->map->map_width = width - 1;
	if (*i < end)
	{
		parse_texture_color(c, *line, order[*i], *i);
		(*i)++;
	}
	else
	{
		new_line = ft_substr(*line, 0, ft_strlen(*line) - 1);
		if (*line)
			free_and_null((void **)line);
		*line = new_line;
		// printf("without newline : %s$\n", *line);
		append_array(*line, &c->map->map_arr, &c->map->map_height);
		// printf("%s", c->map->map_arr[c->map->map_height-1]);
		// printf("height : %d\n", c->map->map_height);
	}
}

void check_map(t_caster *c)
{
	char *line;
	T_Dir i;
	const char *order[6];

	init_var(&i, order);
	line = get_next_line(c->map->map_fd);
	if (!line)
		exit_failure(c, "Empty description.");
	// printf("line: %s", line);
	while (line)
	{
		if (line[0] == '\n' || whole_space_line(line))
		{
			if (i >= end)
				exit_failure(c, "Newline in between the map.");
			if (line)
				free_and_null((void**)&line);
			line = get_next_line(c->map->map_fd);
			// printf("in line: %s***", line);
			continue;
		}
		process_line(c, &line, &i, order);
		if (line)
			free_and_null((void**)&line);
		line = get_next_line(c->map->map_fd);
	}
}

// void	check_map(t_caster *c)
// {
// 	int		width;
// 	char 	*line;
// 	T_Dir	 i;
// 	const char	*order[6];

// 	init_var(&width, &i, order, &line);
// 	while(line)
// 	{
// 		if (line[0] == '\n' || !whole_space_line(line))
// 		{
// 			free(line);
// 			line = getnextline(c->map->map_fd);
// 			continue;
// 		}
// 		if (width > c->map->map_width)
// 			c->map->map_width = width - 1;
// 		if (i < end)
// 		{
// 			parse_texture_color(c, line, order[i]);
// 			i++;
// 		}
// 		else
// 			append_array(line, &c->map->map_arr, &c->map->map_height);
// 		free(line);
// 		line = getnextline(c->map->map_fd);
// 	}
// }