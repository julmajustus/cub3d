/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:35:02 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/25 10:22:41 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	ft_strarr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

static void	set_rbg_color(t_caster *c, char *line, int *rgb)
{
	uint32_t	color;

	color = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 255;
	if (line[0] == 'F')
		c->textures->floor_color = color;
	else
		c->textures->ceiling_color = color;
}

static int	check_digit(char *rgba_arr)
{
	int	i;

	i = 0;
	while (rgba_arr[i])
	{
		while (rgba_arr[i] && ft_isspace(rgba_arr[i]))
			i++;
		if (rgba_arr[i] && !ft_isdigit(rgba_arr[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_rgb_format(t_caster *c, char **rgba_arr, int rgb[3])
{
	int	i;
	int	j;
	int	rgb_value;

	i = 0;
	j = 0;
	while (i < 3)
	{
		while (rgba_arr[i][j] && ft_isspace(rgba_arr[i][j]))
			j++;
		if (!check_digit(rgba_arr[i] + j))
			exit_failure(c, "Invalid format of RGB color : Not a digit");
		rgb_value = ft_atoi(rgba_arr[i] + j);
		if (rgb_value < 0 || rgb_value > 255)
			exit_failure(c, "RGB color range has to be within 0 - 255");
		rgb[i] = rgb_value;
		i++;
		j = 0;
	}
}

void	parse_plain_colors(t_caster *c, char *line)
{
	int		rgb[3];
	char	**rgba_arr;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	rgba_arr = ft_split(line + 1, ',');
	if (!rgba_arr || ft_strarr_len(rgba_arr) != 3)
		exit_failure(c, "Invalid color format, should be 'R,G,B'");
	check_rgb_format(c, rgba_arr, rgb);
	set_rbg_color(c, line, rgb);
	free_arr_and_null(&rgba_arr);
}
