/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_configuration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:24:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/25 15:46:41 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	add_textures(t_caster *c, char *line, char *dir, \
mlx_texture_t	**texture)
{
	char	direction[4];

	direction[0] = line[0];
	direction[1] = line[1];
	direction[2] = line[2];
	direction[3] = '\0';
	if (!ft_strncmp(line, dir, 3) && !*texture)
		*texture = mlx_load_png(c->map->texture_path);
	else
	{
		ft_putstr_fd("Double initailizing in ", 2);
		ft_putstr_fd(direction, 2);
		exit_failure(c, "textures");
	}
}

static void	path_check(t_caster *c, char *texture_path, char *line, t_dir *i)
{
	int	len;

	if (ft_strncmp(texture_path, "./", 2) == 0)
	{
		len = ft_strlen(texture_path);
		while (len > 0 && ft_isspace(texture_path[len - 1]))
			len--;
		texture_path[len] = '\0';
		file_exist(c, texture_path, ".png", TEXTURE);
		c->map->texture_path = texture_path;
		if (*i == 0)
			add_textures(c, line, "NO ", &c->textures->north_texture);
		else if (*i == 1)
			add_textures(c, line, "SO ", &c->textures->south_texture);
		else if (*i == 2)
			add_textures(c, line, "WE ", &c->textures->west_texture);
		else if (*i == 3)
			add_textures(c, line, "EA ", &c->textures->east_texture);
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
		path_check(c, texture_path, line, i);
	}
	else if (!ft_strncmp(line, "F ", 2) && *i == 4)
		parse_plain_colors(c, line);
	else if (!ft_strncmp(line, "C ", 2) && *i == 5)
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
