/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/01 20:31:52 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	exit_mlx(t_caster *c)
{
	mlx_terminate(c ->window->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->window)
		free(c->window);
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
	if (c->window && c->window->handle)
		mlx_terminate(c ->window->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->window)
		free(c->window);
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
