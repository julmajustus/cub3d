/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/16 19:15:53 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	exit_mlx(t_caster *c)
{
	mlx_terminate(c ->img->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->img)
		free(c->img);
	if (c->map)
		free(c->map);
	if (c->textures)
	{
		mlx_delete_texture(c->textures->north_texture);
		mlx_delete_texture(c->textures->south_texture);
		mlx_delete_texture(c->textures->east_texture);
		mlx_delete_texture(c->textures->west_texture);
		free(c->textures);
	}
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_caster *c, char *msg)
{
	if (c->img && c->img->handle)
		mlx_terminate(c ->img->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->img)
		free(c->img);
	if (c->map)
		free(c->map);
	if (c->textures)
	{
		mlx_delete_texture(c->textures->north_texture);
		mlx_delete_texture(c->textures->south_texture);
		mlx_delete_texture(c->textures->east_texture);
		mlx_delete_texture(c->textures->west_texture);
		free(c->textures);
	}
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
