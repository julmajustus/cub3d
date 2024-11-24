/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:30:04 by jmakkone          #+#    #+#             */
/*   Updated: 2024/11/25 00:11:59 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	*malloc_check(t_caster *c, void *ptr)
{
	if (!ptr)
		exit_failure(c, "Malloc failed.");
	return (ptr);
}

char	*safe_itoa(t_caster *c, int n)
{
	return ((char *)malloc_check(c, ft_itoa(n)));
}

char	*safe_strjoin(t_caster *c, const char *s1, const char *s2)
{
	return ((char *)malloc_check(c, ft_strjoin(s1, s2)));
}

char	*safe_substr(t_caster *c, const char *s, unsigned int start, size_t len)
{
	return ((char *)malloc_check(c, ft_substr(s, start, len)));
}

char	*safe_strdup(t_caster *c, const char *s)
{
	return ((char *)malloc_check(c, ft_strdup(s)));
}
