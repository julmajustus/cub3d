/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:35:27 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/17 03:57:07 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	delete_minmap_textures(t_caster *c)
{
	if (c->mmap->wall)
		mlx_delete_texture(c->mmap->wall);
	if (c->mmap->space)
		mlx_delete_texture(c->mmap->space);
	if (c->mmap->door)
		mlx_delete_texture(c->mmap->door);
}

static void	delete_walls(t_caster *c)
{
	if (c->textures->north_texture)
		mlx_delete_texture(c->textures->north_texture);
	if (c->textures->south_texture)
		mlx_delete_texture(c->textures->south_texture);
	if (c->textures->east_texture)
		mlx_delete_texture(c->textures->east_texture);
	if (c->textures->west_texture)
		mlx_delete_texture(c->textures->west_texture);
}

void	free_textures(t_caster *c)
{
	if (c->textures)
	{
		delete_walls(c);
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
		if (c->textures->c_texture)
			mlx_delete_texture(c->textures->c_texture);
		if (c->textures->f_texture)
			mlx_delete_texture(c->textures->f_texture);
		delete_minmap_textures(c);
		free(c->textures);
	}
}
