/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:35:02 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/13 18:13:09 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_rbg_color(t_caster *c, char *line, char **rgba_arr)
{
	int			i;
	uint32_t	color;

	i = 0;
	color = (ft_atoi(rgba_arr[i]) << 24) | (ft_atoi(rgba_arr[i + 1]) << 16) \
								| (ft_atoi(rgba_arr[i + 2]) << 8) | 255;
	if (line[0] == 'F')
		c->textures->floor_color = color;
	else
		c->textures->ceiling_color = color;
}

void	parse_plain_colors(t_caster *c, char *line)
{
	int		i;
	int		j;
	char	**rgba_arr;

	i = 0;
	j = 0;
	rgba_arr = malloc(sizeof(char *) * 4);
	init_arr(rgba_arr, 4);
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	while (line[i])
	{
		if (line[i] == ',')
			j++;
		if (ft_isdigit(line[i]))
			rgba_arr[j] = append_char(rgba_arr[j], line[i]);
		i++;
	}
	if (j != 2)
		exit_failure(c, "Invalid color format");
	set_rbg_color(c, line, rgba_arr);
	free_arr_and_null(&rgba_arr);
}
