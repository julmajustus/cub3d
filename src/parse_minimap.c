/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:31 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/07 00:39:20 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#define MINIMAP_SIZE 100  // 미니맵 창 크기 (300 x 300)
#define PLAYER_CENTER 50 // 미니맵에서 플레이어의 중앙 위치
#define MINIMAP_SCALE 10 // 미니맵 스케일 크기를 고정해줘야댐

// void draw_minimap(t_caster *c, size_t x, size_t y, int flag)
// {
// 	int i;
// 	int j;
// 	uint32_t color;
// 	mlx_image_t *window;

// 	window = c->window->minimap;
// 	if (flag == 1)
// 		color = 0x000000FF;
// 	else if (flag == 3)
// 	{
// 		window = c->window->player;
// 		color = 0x00FF00FF;
// 	}
// 	else
// 		color = 0xFFFFFFFF;
// 	i = -1;
// 	while (++i < c->map->scale_y)
// 	{
// 		j = -1;
// 		while (++j < c->map->scale_x)
// 			mlx_put_pixel(window, x + j, y + i, color);
// 	}
// }

void draw_player_to_minimap(t_caster *c)
{
	// draw_minimap(c, c->mmap_px, c->mmap_py, 3);
	printf("Player pos X: %f Y: %f\n", c->mmap_px, c->mmap_py);
	printf("speed_multiplier: %f\n", c->speed_multiplier);
}

// void parse_minimap(t_caster *c)
// {
// 	size_t x;
// 	size_t y;
// 	size_t xo;
// 	size_t yo;

// 	y = -1;
// 	while (++y < (size_t)c->map->map_height)
// 	{
// 		x = -1;
// 		while (++x < ft_strlen(c->map->map_arr[y]))
// 		{
// 			xo = x * c->map->scale_x;
// 			yo = y * c->map->scale_y;
// 			if (c->map->map_arr[y][x] == '1')
// 				draw_minimap(c, xo, yo, 1);
// 			else if (c->map->map_arr[y][x] == '0')
// 				draw_minimap(c, xo, yo, 0);
// 			else if (ft_strchr("NSEW", c->map->map_arr[y][x]))
// 				draw_minimap(c, xo, yo, 0);
// 		}
// 	}
// }



// 타일을 그리는 함수
void draw_minimap(t_caster *c, int x, int y, int flag)
{
	int i, j;
	uint32_t color;
	
	if (flag == 1)
		color = 0x000000FF;
	if (flag == 0)
		color = 0xFFFFFF; // 벽은 검은색, 빈 공간은 흰색
	if (flag == 2)
		color = 0xFF0000;
	mlx_image_t *window = c->window->minimap; // 미니맵 윈도우에 그리기
	i = -1;
	while (++i < c->map->scale_y)
	{
		j = -1;
		while (++j < c->map->scale_x)
			mlx_put_pixel(window, x + j, y + i, color); // 타일에 색상을 채움
	}
}

// 미니맵을 그릴 때 사용될 오프셋을 계산하고 화면 크기 내에서만 그리기


void parse_minimap(t_caster *c)
{
	// 원본 맵을 축소한 미니맵을 전체로 그리기 위해 스케일 계산
	c->map->scale_x = MINIMAP_SCALE; //1보다 커야댐
	c->map->scale_y = MINIMAP_SCALE;
	// 원본 맵을 축소한 미니맵을 전체로 그리기 위해 스케일 계산
	// c->map->scale_x = MINIMAP_SIZE / c->map->map_width;	 // 고정된 크기로 비율 계산
	// c->map->scale_y = MINIMAP_SIZE / c->map->map_height; // 고정된 크기로 비율 계산

	int i = 0;
	mlx_image_t *window = c->window->minimap;
	while (i < MINIMAP_SIZE) // height
	{
		int j = 0;
		while (j < MINIMAP_SIZE)
		{
			// 맵이 미니맵을 벗어난 경우 다른 색으로 칠함
			if (i >= c->map->map_height || j >= c->map->map_width)
			{
				mlx_put_pixel(window, j, i, 0xAAAAAA); // 벗어난 부분은 회색
			}
			j++;
		}
		i++;
	}
	// 플레이어가 미니맵 중앙에 위치하도록 카메라 오프셋 계산 
	//즉 camerao
	// int로 해준이유는 소수값정리하기위해서 +0.201인가 넣어줌// player_center을 빼주면서
	int camera_offset_x = (int)(c->px * c->map->scale_x) - PLAYER_CENTER;
	int camera_offset_y = (int)(c->py * c->map->scale_y) - PLAYER_CENTER;

	// 미니맵의 범위 제한 (오프셋이 미니맵 경계를 넘지 않도록)
	if (c->map->map_width * c->map->scale_x < MINIMAP_SIZE)
	{
		// 맵의 크기가 미니맵보다 작은 경우, 중앙 정렬
		camera_offset_x = (c->map->map_width * c->map->scale_x - MINIMAP_SIZE) / 2;
	}
	else if (camera_offset_x > (c->map->map_width * c->map->scale_x) - MINIMAP_SIZE)
	{
		// 넘지않도록 미니맵윈도우크기 , 오프셋 조정
		camera_offset_x = (c->map->map_width * c->map->scale_x) - MINIMAP_SIZE;
	}

	if (c->map->map_height * c->map->scale_y < MINIMAP_SIZE)
	{
		// 맵의 크기가 미니맵보다 작은 경우, 중앙 정렬
		camera_offset_y = (c->map->map_height * c->map->scale_y - MINIMAP_SIZE) / 2;
	}
	else if (camera_offset_y > (c->map->map_height * c->map->scale_y) - MINIMAP_SIZE)
	{
		camera_offset_y = (c->map->map_height * c->map->scale_y) - MINIMAP_SIZE;
	}

	int y = 0;
	while (y < c->map->map_height && c->map->map_arr[y])
	{
		int x = 0;
		while (x < c->map->map_width && c->map->map_arr[y][x])
		{
			int minimap_x = (int)(x * c->map->scale_x) - camera_offset_x;
			int minimap_y = (int)(y * c->map->scale_y) - camera_offset_y;

			if (minimap_x < 0)
				minimap_x = 0;
			else if (minimap_x >= MINIMAP_SIZE)
				minimap_x = MINIMAP_SIZE - 1;

			if (minimap_y < 0)
				minimap_y = 0;
			else if (minimap_y >= MINIMAP_SIZE)
				minimap_y = MINIMAP_SIZE - 1;

			// printf("map[%d][%d] : %d\n", y, x, c->map->map_arr[y][x]);
			char tile = c->map->map_arr[y][x];
			if (tile == '1')
				draw_minimap(c, minimap_x, minimap_y, 1); // 벽 타일
			else if (tile == '0')
				draw_minimap(c, minimap_x, minimap_y, 0); // 빈 공간
			x++;
		}
		y++;
	}

	// 플레이어를 미니맵에 그리기 (플레이어 위치는 항상 일정하게 표시)
	//  플레이어의 위치 계산 (camera_offset 고려)
	int player_x = (int)(c->px * c->map->scale_x) - camera_offset_x;
	int player_y = (int)(c->py * c->map->scale_y) - camera_offset_y;

	// 미니맵 경계를 넘지 않도록 제한
	if (player_x < 0)
		player_x = 0;
	else if (player_x >= MINIMAP_SIZE)
		player_x = MINIMAP_SIZE - 1;

	if (player_y < 0)
		player_y = 0;
	else if (player_y >= MINIMAP_SIZE)
		player_y = MINIMAP_SIZE - 1;

	// 맵 인덱스를 계산할 때 scale_x와 scale_y로 나눈 후 범위 체크
	printf("player_x : %d\n player_y : %d\n", player_x,  player_y);
	// int map_x = (int)(player_x / c->map->scale_x);
	// int map_y = (int)(player_y / c->map->scale_y);
	int map_x = (int)(c->px); // px는 실제 좌표이므로 바로 인덱스로 사용
	int map_y = (int)(c->py);

	// map_arr의 범위가 유효한지 확인
	if (map_x >= 0 && map_x < c->map->map_width && map_y >= 0 && map_y < c->map->map_height)
	{
		// 디버깅용 출력
		printf("map_arr[%d][%d] : %c\n", map_y, map_x, c->map->map_arr[map_y][map_x]);

		// 벽이 있는지 체크
		if (c->map->map_arr[map_y][map_x] == '1')
		{
			// 벽에 부딪히지 않도록 수정
			if (player_x < 0)
				player_x = 0;
			else if (player_x >= MINIMAP_SIZE)
				player_x = MINIMAP_SIZE - 1;

			if (player_y < 0)
				player_y = 0;
			else if (player_y >= MINIMAP_SIZE)
				player_y = MINIMAP_SIZE - 1;
		}
	}
	else
	{
		// 인덱스가 범위를 벗어나는 경우 처리
		printf("Invalid map indices: map_x = %d, map_y = %d\n", map_x, map_y);
	}

	// 미니맵에 플레이어 그리기
	draw_minimap(c, player_x, player_y, 2);

	// draw_minimap(c, PLAYER_CENTER, PLAYER_CENTER, 2);
}
