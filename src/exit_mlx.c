/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/27 04:40:56 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	free_sprites(t_caster *c)
{
	int	i;

	i = -1;
	while (++i < c->max_sprite_count)
	{
		if (c->sp[i])
			free(c->sp[i]);
	}
	if (c->sp)
		free(c->sp);
}

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
	if (c->gun)
		free(c->gun);
	if (c->mmap)
		free(c->mmap);
	if (c->valid_spawn_points)
		free(c->valid_spawn_points);
}

static void	free_pixel_buffers(t_caster *c)
{
	if (c->no_wall_pixel_buffer)
		free(c->no_wall_pixel_buffer);
	if (c->so_wall_pixel_buffer)
		free(c->so_wall_pixel_buffer);
	if (c->we_wall_pixel_buffer)
		free(c->we_wall_pixel_buffer);
	if (c->ea_wall_pixel_buffer)
		free(c->ea_wall_pixel_buffer);
	if (c->door_pixel_buffer)
		free(c->door_pixel_buffer);
	if (c->exit_pixel_buffer)
		free(c->exit_pixel_buffer);
	if (c->ceiling_pixel_buffer)
		free(c->ceiling_pixel_buffer);
	if (c->floor_pixel_buffer)
		free(c->floor_pixel_buffer);
	if (c->sp_pixel_buffer)
		free(c->sp_pixel_buffer);
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
	if (c->map_row_len_buffer)
		free(c->map_row_len_buffer);
	free_textures(c);
	free_structs(c);
	free_sprites(c);
	free_pixel_buffers(c);
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
	if (c->map_row_len_buffer)
		free(c->map_row_len_buffer);
	free_textures(c);
	free_structs(c);
	free_sprites(c);
	free_pixel_buffers(c);
	perror(msg);
	exit(EXIT_FAILURE);
}
