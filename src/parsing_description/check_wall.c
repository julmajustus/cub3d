/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:09 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/13 19:18:29 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_array(t_caster *c, int ***visited)
{
	int	i;
	int	j;

	*visited = malloc(c->map->map_height * sizeof(int *));
	if (!*visited)
		exit_failure(c, "Memory allocation failed for visited array.");
	i = -1;
	while (++i < c->map->map_height)
	{
		(*visited)[i] = malloc(c->map->map_width * sizeof(int));
		if (!(*visited)[i])
		{
			j = -1;
			while (++j < i)
				free((*visited)[j]);
			free(*visited);
			exit_failure(c, "Memory allocation failed for visited row.");
		}
	}
}

static int	check_dfs(t_caster *c, int y, int x, int **visited)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (y < 0 || y >= c->map->map_height || x < 0 || c->map->map_arr[y] == 0 \
		|| (size_t)x >= ft_strlen(c->map->map_arr[y]) \
		|| c->map->map_arr[y][x] == ' ')
		return (false);
	if (visited[y][x] || c->map->map_arr[y][x] == '1')
		return (true);
	visited[y][x] = true;
	if (c->map->map_arr[y][x] == 'W' || c->map->map_arr[y][x] == 'N' \
		|| c->map->map_arr[y][x] == 'E' || c->map->map_arr[y][x] == 'S')
		c->map->map_arr[y][x] = '0';
	up = check_dfs(c, y - 1, x, visited);
	down = check_dfs(c, y + 1, x, visited);
	left = check_dfs(c, y, x - 1, visited);
	right = check_dfs(c, y, x + 1, visited);
	return (up && down && left && right);
}

void	check_wall(t_caster *c)
{
	int	**visited;
	int	i;
	int	j;

	init_array(c, &visited);
	i = -1;
	while (++i < c->map->map_height)
	{
		j = -1;
		while (++j < c->map->map_width)
			visited[i][j] = false;
	}
	if (!check_dfs(c, c->py - 0.201, c->px - 0.201, visited))
		exit_failure(c, "map is not covered by walls.");
	i = -1;
	while (++i < c->map->map_height)
		free(visited[i]);
	free(visited);
}
