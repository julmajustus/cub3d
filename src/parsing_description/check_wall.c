/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:09 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/12 18:44:30 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_dfs(t_caster *c, int y, int x, int visited[c->map->map_height][c->map->map_width])
{
    int up;
    int down;
    int left;
    int right;

    if (y < 0 || y >= c->map->map_height || x < 0 || c->map->map_arr[y] == NULL ||(size_t)x >= ft_strlen(c->map->map_arr[y]) || c->map->map_arr[y][x] == ' ')
        return (false);
    if (visited[y][x] || c->map->map_arr[y][x] == '1')
        return (true);
    visited[y][x] = true;
    if (c->map->map_arr[y][x] == 'W' || c->map->map_arr[y][x] == 'N' || c->map->map_arr[y][x] == 'E' || c->map->map_arr[y][x] == 'S')
        // printf("Changing tile at [%d][%d] from '%c' to '0'\n", y, x, c->map->map_arr[y][x]);
        c->map->map_arr[y][x] = '0';
    up = check_dfs(c, y - 1, x, visited);
    down = check_dfs(c, y + 1, x, visited);
    left = check_dfs(c, y, x - 1, visited);
    right = check_dfs(c, y, x + 1, visited);
    return (up && down && left && right);
}

void change_empty_to_space(t_caster *c)
{
    int i;
    int j;

    i = 0;
    while (i < c->map->map_height)
    {
        j = 0;
        while (j < (int)ft_strlen(c->map->map_arr[i]))
        {
            if (ft_isspace(c->map->map_arr[i][j]))
                c->map->map_arr[i][j] = '0';
            j++;
        }
        i++;
    }
}

void check_wall(t_caster *c)
{
    int visited[c->map->map_height][c->map->map_width];
    int i;
    int j;

    i = 0;
    while (i < c->map->map_height)
    {
        j = 0;
        while (j < c->map->map_width)
        {
            visited[i][j] = false;
            j++;
        }
        i++;
    }
    if (!check_dfs(c, c->py - 0.201, c->px - 0.201, visited))
        exit_failure(c, "Map does not covered by walls.");
    //change_empty_to_space(c);
}
