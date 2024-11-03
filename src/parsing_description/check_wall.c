/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:09 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/03 11:36:18 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// #include <stdbool.h> // bool 타입을 사용하려면 필요합니다.

// bool check_dfs(t_caster *c, int y, int x, bool visited[c->map->map_height][c->map->map_width])
// {
//     if (y < 0 || y >= c->map->map_height || x < 0 || x >= c->map->map_width)
//         return false; // 경계를 벗어나면 false 반환

//     if (visited[y][x] || c->map->map_arr[y][x] == '1')
//         return true; // 이미 방문했거나 벽인 경우 true 반환 (문제 없음)

//     visited[y][x] = true;

//     // 현재 위치가 W, N, E, S 중 하나라면 '0'으로 변경
//     if (c->map->map_arr[y][x] == 'W' ||
//         c->map->map_arr[y][x] == 'N' || c->map->map_arr[y][x] == 'E' ||
//         c->map->map_arr[y][x] == 'S')
//     {
//         c->map->map_arr[y][x] = '0';
//     }

//     // 현재 위치가 빈 공간이라면 '1'로 변경
//     if (c->map->map_arr[y][x] == ' ')
//         c->map->map_arr[y][x] = '1';

//     // 네 방향을 탐색
//     bool up = check_dfs(c, y - 1, x, visited);
//     bool down = check_dfs(c, y + 1, x, visited);
//     bool left = check_dfs(c, y, x - 1, visited);
//     bool right = check_dfs(c, y, x + 1, visited);

//     // 하나라도 성공적으로 탐색을 마치면 true 반환
//     return (up || down || left || right);
// }

// void check_wall(t_caster *c)
// {
//     bool visited[c->map->map_height][c->map->map_width]; // Ensure correct size
//     int i, j;

//     // Initialize visited array
//     for (i = 0; i < c->map->map_height; i++)
//     {
//         for (j = 0; j < c->map->map_width; j++)
//         {
//             visited[i][j] = false;
//         }
//     }

//     // Perform DFS from the starting position
//     if (!check_dfs(c, c->py - 0.0001, c->px - 0.0001, visited))
//         exit_failure(c, "Map does not covered by walls.");
// }

int check_dfs(t_caster *c, int y, int x, int visited[c->map->map_height][c->map->map_width])
{
    int up;
    int down;
    int left;
    int right;
    // printf("Hieght, Width : (%d, %d): visited = %d, value = %c\n", c->map->map_height, c->map->map_width, visited[y][x], c->map->map_arr[y][x]);
    // printf("Checking position (y, x) : (%d, %d): visited = %d, value = %c\n", y, x, visited[y][x], c->map->map_arr[y][x]);

    if (y < 0 || y >= c->map->map_height || x < 0 || c->map->map_arr[y] == NULL ||(size_t)x >= ft_strlen(c->map->map_arr[y]))
        return (false);
    if (visited[y][x] || c->map->map_arr[y][x] == '1')
        return (true);
    visited[y][x] = true;
    if (c->map->map_arr[y][x] == ' ' ||   c->map->map_arr[y][x] == 'W' \
     || c->map->map_arr[y][x] == 'N' || c->map->map_arr[y][x] == 'E' \
     || c->map->map_arr[y][x] == 'S')
        c->map->map_arr[y][x] = '0';
    up = check_dfs(c, y - 1, x, visited);
    down = check_dfs(c, y + 1, x, visited);
    left = check_dfs(c, y, x - 1, visited);
    right = check_dfs(c, y, x + 1, visited);
    return (up && down && left && right);
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
    if (!check_dfs(c, c->py - 0.0001, c->px - 0.0001, visited))
        exit_failure(c, "Map does not covered by walls.");
}