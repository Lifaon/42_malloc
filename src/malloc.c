/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:08:34 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/11 18:20:14 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/errno.h>
#include "zone.h"

#include <stdio.h>

static t_zone	*create_zone(t_kind kind, size_t size)
{
	t_zone	*zone;
	int		i;

	zone = (t_zone *)mmap(NULL, sizeof(t_zone), PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zone)
		return (NULL);
	zone->ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zone->ptr)
	{
		munmap(zone, sizeof(t_zone));
		return (NULL);
	}
	zone->kind = kind;
	zone->size = size;
	i = -1;
	while (i < 128)
		zone->allocated[i++] = 0;
	zone->next = NULL;
	return (zone);
}

static t_zone	*get_next_available_zone(t_zone *zone, int *i)
{
	t_zone	*tmp;
	int		limit;

	tmp = zone;
	limit = tmp->kind == LARGE ? 1 : 128;
	while (tmp)
	{
		*i = -1;
		while (++(*i) < limit)
			if (!tmp->allocated[*i])
				return (tmp);
		tmp = tmp->next;
	}
	*i = 0;
	return (NULL);
}

static void		*allocate_memory(t_zone *zone)
{
	t_zone	*tmp;
	void	*ptr;
	int		i;

	tmp = get_next_available_zone(zone, &i);
	if (!tmp)
	{
		tmp = zone;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = create_zone(tmp->kind, tmp->size)))
			return (NULL);
		tmp = tmp->next;
	}
	tmp->allocated[i] = 1;
	ptr = tmp->ptr;
	if (zone->kind == TINY)
		ptr += g_data.tiny_coeff * i;
	else if (zone->kind == SMALL)
		ptr += g_data.small_coeff * i;
	return (ptr);
}

void			*malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	else if (size <= g_data.tiny_coeff)
	{
		if (!g_data.tiny)
			if (!(g_data.tiny = create_zone(TINY, g_data.tiny_size)))
				return (NULL);
		return (allocate_memory(g_data.tiny));
	}
	else if (size <= g_data.small_coeff)
	{
		if (!g_data.small)
			if (!(g_data.small = create_zone(SMALL, g_data.small_size)))
				return (NULL);
		return (allocate_memory(g_data.small));
	}
	if (!g_data.large)
		if (!(g_data.large = create_zone(LARGE, size)))
			return (NULL);
	return (allocate_memory(g_data.large));
}
