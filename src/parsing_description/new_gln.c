/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gln.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:11:48 by skwon2            #+#    #+#             */
/*   Updated: 2024/11/13 18:11:32 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	store_line(t_line *line_data, int fd)
{
	int	i;

	i = line_data->line_index;
	while (1)
	{
		if (line_data->buff_index >= line_data->read_byte)
		{
			line_data->read_byte = read(fd, line_data->buffer, BUFFER_SIZE);
			line_data->buff_index = 0;
			if (line_data->read_byte <= 0)
				break ;
		}
		if (line_data->buffer[line_data->buff_index] == '\n')
		{
			line_data->line[i++] = line_data->buffer[line_data->buff_index++];
			break ;
		}
		line_data->line[i++] = line_data->buffer[line_data->buff_index++];
	}
	line_data->line[i] = '\0';
	line_data->line_index = i;
}

char	*get_next_line(int fd)
{
	static t_line	line_data;

	line_data.line_index = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		perror("Invalid Buffer_size or fd");
		return (NULL);
	}
	store_line(&line_data, fd);
	if (line_data.line_index == 0)
		return (NULL);
	return (ft_strdup(line_data.line));
}
