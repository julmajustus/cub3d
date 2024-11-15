/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/15 15:05:55 by jmakkone         ###   ########.fr       */
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
		if (c->textures->sp_texture)
			mlx_delete_texture(c->textures->sp_texture);
		if (c->textures->start_screen)
			mlx_delete_texture(c->textures->start_screen);
		if (c->textures->menu_screen)
			mlx_delete_texture(c->textures->menu_screen);
		if (c->textures->death_screen)
			mlx_delete_texture(c->textures->death_screen);
		if (c->gun->texture)
			mlx_delete_texture(c->gun->texture);
		if (c->mmap->wall)
			mlx_delete_texture(c->mmap->wall);
		if (c->mmap->space)
			mlx_delete_texture(c->mmap->space);
		if (c->mmap->door)
			mlx_delete_texture(c->mmap->door);
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
	if (c->depth_buffer)
		free(c->depth_buffer);
	if (c->map_row_len_buffer)
		free(c->map_row_len_buffer);
	free_textures(c);
	free_structs(c);
	free_sprites(c);
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
	if (c->depth_buffer)
		free(c->depth_buffer);
	if (c->map_row_len_buffer)
		free(c->map_row_len_buffer);
	free_textures(c);
	free_structs(c);
	free_sprites(c);
	perror(msg);
	exit(EXIT_FAILURE);
}
