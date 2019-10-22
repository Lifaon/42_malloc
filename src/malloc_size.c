/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:12:01 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/22 14:31:35 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mymalloc.h"

size_t	malloc_good_size(size_t size)
{
	static size_t	page_size = 0;
	static size_t	tiny = 0;
	static size_t	small = 0;

	if (!page_size)
	{
		page_size = getpagesize();
		tiny = page_size / 256;
		small = page_size * 32 / 128;
	}
	if (size < tiny)
		return (tiny);
	else if (size < small)
		return (small);
	return ((size + (page_size - 1)) & ~(page_size - 1));
}

size_t	malloc_size(const void *ptr)
{
	t_zone	*zone;
	int		i;

	match_zone_ptr(&zone, (void *)ptr, &i);
	if (!zone)
		return (0);
	return (zone->size / zone->limit);
}
