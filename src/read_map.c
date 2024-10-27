/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:11:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/23 19:29:55 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int parse_plain_colors(t_caster *c, char *line)
{
	int			i;
	int			j;
	uint32_t	color;
	char 		**rgba_arr;

	i = -1;
	j = 0;
	rgba_arr = malloc(sizeof(char *) * 4);
	init_arr(rgba_arr, 4);
	while (line[++i] && !ft_isdigit(line[i]))
		;
	while (line[i])
	{
		if (line[i] == ',')
			j++;
		if (ft_isdigit(line[i]))
			rgba_arr[j] = append_char(rgba_arr[j], line[i]);
		i++;
	}
	i = 0;
	if (j != 2)
	{
		exit_failure(c, "Parsing of plain colors have failed");
		return (0);
	}
	color = (ft_atoi(rgba_arr[i]) << 24) \
		| (ft_atoi(rgba_arr[i + 1]) << 16) \
		| (ft_atoi(rgba_arr[i + 2]) << 8) \
		| 255;
//		| (ft_atoi(rgba_arr[i + 3]));
	if (line[0] == 'F')
		c->textures->floor_color = color;
	else
		c->textures->ceiling_color = color;
	return(1);
}

static int	parse_textures(t_caster *c, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (1);//collect texture or rgb
	else if (!ft_strncmp(line, "SO ", 3))
		return (1);//collect texture or rgb
	else if (!ft_strncmp(line, "WE ", 3))
		return (1);//collect texture or rgb
	else if (!ft_strncmp(line, "EA ", 3))
		return (1);//collect texture or rgb
	else if (!ft_strncmp(line, "F ", 2))
		return (parse_plain_colors(c, line));//collect texture or rgb
	else if (!ft_strncmp(line, "C ", 2))
		return (parse_plain_colors(c, line));//collect texture or rgb
	return (0);
}

static void	set_player_direction(t_caster *c, size_t x, size_t y)
{
	if (c->map->map_arr[y][x] == 'N')
		c->view_angle = -M_PI_2; // 90 degrees
	else if (c->map->map_arr[y][x] == 'S')
		c->view_angle = M_PI_2; // -90 degrees
	else if (c->map->map_arr[y][x] == 'E')
		c->view_angle = 0; // 0 degrees (facing east)
	else if (c->map->map_arr[y][x] == 'W')
		c->view_angle = M_PI; // 180 degrees (facing west)
}

static void	find_player_pos(t_caster *c)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < (size_t)c->map->map_height)
	{
		x = -1;
		while (++x < ft_strlen(c->map->map_arr[y]))
		{
			if (c->map->map_arr[y][x] == 'N' || c->map->map_arr[y][x] == 'S' ||\
				c->map->map_arr[y][x] == 'W' || c->map->map_arr[y][x] == 'E')
			{
				c->px = x + 0.0001;
				c->py = y + 0.0001;
				c->mmap_px = x * c->map->scale_x + 0.0001;
				c->mmap_py = y * c->map->scale_y + 0.0001;
				set_player_direction(c, x, y);
				break ;
			}
		}
	}
}

void	read_map(t_caster *c, char **av)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		if (!parse_textures(c, line))
		{
			if (ft_strlen(line) > (size_t)c->map->map_width)
				c->map->map_width = ft_strlen(line) - 1;
			append_array(line, &c->map->map_arr, &c->map->map_height);
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	c->map->scale_x = (double)((WIDTH / 5) / c->map->map_width);
	c->map->scale_y = (double)((HEIGHT / 5) / c->map->map_height);
	find_player_pos(c);
}
