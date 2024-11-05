/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/05 09:39:09 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void exit_mlx(t_caster *c)
{
	mlx_terminate(c->window->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->map->map_fd > -1)
		close(c->map->map_fd);
	if (c->map->texture_fd > -1)
		close(c->map->texture_fd);
	if (c->map->texture_path)
		free(c->map->texture_path);
	if (c->map)
		free(c->map);
	if (c->window)
		free(c->window);
	if (c->textures)
	{
		if (c->textures->north_texture)
			mlx_delete_texture(c->textures->north_texture);
		if (c->textures->south_texture)
			mlx_delete_texture(c->textures->south_texture);
		if (c->textures->east_texture)
			mlx_delete_texture(c->textures->east_texture);
		if (c->textures->west_texture)
			mlx_delete_texture(c->textures->west_texture);
		free(c->textures);
	}
	exit(EXIT_SUCCESS);
}

void exit_failure(t_caster *c, char *msg)
{
	if (c->window && c->window->handle)
		mlx_terminate(c->window->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->map->map_fd > -1)
		close(c->map->map_fd);
	if (c->map->texture_fd > -1)
		close(c->map->texture_fd);
	if (c->map->texture_path)
		free(c->map->texture_path);
	if (c->map)
		free(c->map);
	if (c->window)
		free(c->window);
	if (c->textures)
	{
		if (c->textures->north_texture)
			mlx_delete_texture(c->textures->north_texture);
		if (c->textures->south_texture)
			mlx_delete_texture(c->textures->south_texture);
		if (c->textures->east_texture)
			mlx_delete_texture(c->textures->east_texture);
		if (c->textures->west_texture)
			mlx_delete_texture(c->textures->west_texture);
		free(c->textures);
	}
	// printf("%s\n", msg);
	perror(msg);
	exit(EXIT_FAILURE);
}
