/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_configuration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:24:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/25 00:08:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	path_check(t_caster *c, char *texture_path, char *line)
{
	int	len;

	if (ft_strncmp(texture_path, "./", 2) == 0)
	{
		len = ft_strlen(texture_path);
		while (len > 0 && ft_isspace(texture_path[len - 1]))
			len--;
		texture_path[len] = '\0';
		file_exist(c, texture_path, ".png", TEXTURE);
		if (!ft_strncmp(line, "NO ", 3))
			c->textures->north_texture = mlx_load_png(texture_path);
		else if (!ft_strncmp(line, "SO ", 3))
			c->textures->south_texture = mlx_load_png(texture_path);
		else if (!ft_strncmp(line, "WE ", 3))
			c->textures->west_texture = mlx_load_png(texture_path);
		else if (!ft_strncmp(line, "EA ", 3))
			c->textures->east_texture = mlx_load_png(texture_path);
		free_and_null((void **)&c->map->texture_path);
	}
	else
		exit_failure(c, "Texture path must start with './'");
}

static void	parse_texture_color(t_caster *c, char *line, t_dir *i)
{
	char	*texture_path;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
	!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		texture_path = line + 3;
		while (ft_isspace(*texture_path))
			texture_path++;
		path_check(c, texture_path, line);
	}
	else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		parse_plain_colors(c, line);
	else
		exit_failure(c, "There is wrong text in between the description.");
	(*i)++;
}

void	init_var(t_dir *i, const char **order)
{
	order[0] = "NO ";
	order[1] = "SO ";
	order[2] = "WE ";
	order[3] = "EA ";
	order[4] = "F ";
	order[5] = "C ";
	*i = NO;
}

void	process_line(t_caster *c, char **line, t_dir *i)
{
	int	width;
	int	index;
	int	len;

	index = 0;
	width = ft_strlen(*line);
	if (width > c->map->map_width)
		c->map->map_width = width - 1;
	if (*i < end)
	{
		while ((*line)[index] && ((*line)[index] == ' ' \
			|| ((*line)[index] >= 9 && (*line)[index] <= 13)))
			index++;
		parse_texture_color(c, *line + index, i);
	}
	else
	{
		len = ft_strlen(*line);
		if (len > 0 && (*line)[len - 1] == '\n')
			(*line)[len - 1] = '\0';
		if (ft_strchr(*line, 'D'))
			store_door_info(c, *line);
		if (append_array(*line, &c->map->map_arr, &c->map->map_height))
			exit_failure(c, "append array failed.");
	}
}

void	check_map(t_caster *c)
{
	char	*line;
	t_dir	i;

	i = NO;
	line = get_next_line(c->map->map_fd);
	if (!line)
		exit_failure(c, "Empty description.");
	while (line)
	{
		if (whole_space_line(line))
		{
			if (i >= end && c->map->map_arr && c->map->map_arr[0])
				exit_failure(c, "Newline in between the map.");
			if (line)
				free_and_null((void **)&line);
			line = get_next_line(c->map->map_fd);
			continue ;
		}
		process_line(c, &line, &i);
		if (line)
			free_and_null((void **)&line);
		line = get_next_line(c->map->map_fd);
	}
}
