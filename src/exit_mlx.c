/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/13 22:40:59 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	free_structs(t_caster *c)
{
	if (c->map)
		free(c->map);
	if (c->window)
		free(c->window);
	if (c->doors)
		free(c->doors);
	if (c->ta)
		free(c->ta);
	if (c->sp)
		free(c->sp);
	if (c->gun)
		free(c->gun);
	if (c->mmap)
		free(c->mmap);
}

static void	free_textures(t_caster *c)
{
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
		if (c->textures->door_texture)
			mlx_delete_texture(c->textures->door_texture);
		if (c->sp->texture)
			mlx_delete_texture(c->sp->texture);
		if (c->gun->texture)
			mlx_delete_texture(c->gun->texture);
		if (c->mmap->wall)
			mlx_delete_texture(c->mmap->wall);
		if (c->mmap->space)
			mlx_delete_texture(c->mmap->space);
		free(c->textures);
	}
}

void	exit_mlx(t_caster *c)
{
	mlx_terminate(c->window->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->map->map_fd > -1)
		close(c->map->map_fd);
	if (c->map->texture_fd > -1)
		close(c->map->texture_fd);
	free_textures(c);
	free_structs(c);
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_caster *c, char *msg)
{
	if (c->window && c->window->handle)
		mlx_terminate(c->window->handle);
	if (c->map->map_arr)
		free_arr_and_null(&c->map->map_arr);
	if (c->map->map_fd > -1)
		close(c->map->map_fd);
	if (c->map->texture_fd > -1)
		close(c->map->texture_fd);
	free_textures(c);
	free_structs(c);
	perror(msg);
	exit(EXIT_FAILURE);
}
