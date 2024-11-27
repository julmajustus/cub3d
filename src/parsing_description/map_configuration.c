/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_configuration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:24:03 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/27 19:47:23 by jmakkone         ###   ########.fr       */
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
		c->map->texture_path = texture_path;
		if (!ft_strncmp(line, "NO ", 3))
			add_textures(c, line, "NO ", &c->textures->north_texture);
		else if (!ft_strncmp(line, "SO ", 3))
			add_textures(c, line, "SO ", &c->textures->south_texture);
		else if (!ft_strncmp(line, "WE ", 3))
			add_textures(c, line, "WE ", &c->textures->west_texture);
		else if (!ft_strncmp(line, "EA ", 3))
			add_textures(c, line, "EA ", &c->textures->east_texture);
	}
	else
		exit_failure(c, "Texture path must start with './'");
}

static void	parse_texture_color(t_caster *c, char *line, int *line_check)
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
	else if (!ft_strncmp(line, "F ", 2))
		parse_plain_colors(c, line);
	else if (!ft_strncmp(line, "C ", 2))
		parse_plain_colors(c, line);
	else
		exit_failure(c, "There is wrong text in between the description.");
	(*line_check)++;
}

static void	processing(t_caster *c, char **line, int *line_check)
{
	int	len;
	int	index;

	index = 0;
	if (*line_check < end)
	{
		while ((*line)[index] && ((*line)[index] == ' ' \
		|| ((*line)[index] >= 9 && (*line)[index] <= 13)))
			index++;
		parse_texture_color(c, *line + index, line_check);
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

void	process_line(t_caster *c, char **line, int *line_check)
{
	int	width;

	width = ft_strlen(*line);
	if (width > 2500)
		exit_failure(c, "over the limit of map width");
	if (width > c->map->map_width)
		c->map->map_width = width - 1;
	processing(c, line, line_check);
}
