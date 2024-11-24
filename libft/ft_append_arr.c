/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/25 00:21:04 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	append_array(char *content, char ***new_arr, int *new_arr_size)
{
	*new_arr = ft_realloc(*new_arr, \
					sizeof(char *) * *new_arr_size, \
					sizeof(char *) * (*new_arr_size + 2));
	if (!*new_arr)
	{
		write(2, "append array realloc failed!", 28);
		return (1);
	}
	if (content)
	{
		(*new_arr)[*new_arr_size] = ft_strdup(content);
		if (!(*new_arr)[*new_arr_size])
		{
			write(2, "append array strdup failed!", 27);
			return (1);
		}
		*new_arr_size += 1;
	}
	(*new_arr)[*new_arr_size] = NULL;
	return (0);
}
