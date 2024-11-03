/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:31:29 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/03 09:05:27 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void file_exist(t_caster *c, char *file, char *extension, int i)
{
	int	len;
	// printf("texture file name : %s\n", c->map->texture_path);
	// printf("file name : %s\n", file);
	len = ft_strlen(file);
	if (i == MAP)
		c->map->map_fd = open(file, O_RDONLY);
	else if (i == TEXTURE)
		c->map->texture_fd = open(file, O_RDONLY);
	if (c->map->map_fd == -1 || c->map->texture_fd == -1) 
		exit_failure(c, "Error opening file : check if it is the right path.");
	if (len < 4 || ft_strcmp(file + len - 4, extension) != 0)
        exit_failure(c, "Does not match with extension format.");
}
