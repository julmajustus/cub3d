/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_door_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 03:53:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/23 03:55:40 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	reset_door_state(t_caster *c)
{
	int	i;

	i = -1;
	while (++i < c->door_count)
		c->doors[i].is_open = 0;
}
