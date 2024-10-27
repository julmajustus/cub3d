/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:53:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/02 09:37:22 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_null(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}
