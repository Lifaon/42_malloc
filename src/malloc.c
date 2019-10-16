/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:08:34 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/16 10:56:08 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "mymalloc.h"

static void		*allocate(size_t size)
{
	return (mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0));
}

static t_zone	*create_zone(t_zone *zone, t_kind kind, size_t size)
{
	t_zone	*new;
	int		i;

	if (!(new = (t_zone *)allocate(sizeof(t_zone))))
		return (NULL);
	if (size && !(new->ptr = allocate(size)))
	{
		munmap(new, sizeof(t_zone));
		return (NULL);
	}
	new->kind = kind;
	new->is_root = zone == NULL ? 1 : 0;
	new->size = size;
	new->limit = kind == LARGE ? 1 : 128;
	new->areas_left = new->limit;
	i = -1;
	while (i < new->limit)
		new->allocated[i++] = 0;
	new->prev = zone ? zone->prev : new;
	new->next = zone ? zone : new;
	zone && (zone->prev->next = new);
	zone && (zone->prev = new);
	return (new);
}

static t_zone	*get_next_available_zone(t_zone *zone, int *i)
{
	t_zone	*tmp;

	tmp = zone;
	while (1)
	{
		if (tmp->areas_left > 0)
		{
			*i = -1;
			while (++(*i) < zone->limit)
				if (!tmp->allocated[*i])
					return (tmp);
		}
		tmp = tmp->next;
		if (tmp->is_root)
			break ;
	}
	*i = 0;
	return (NULL);
}

static void		*allocate_memory(t_zone *zone, size_t size)
{
	t_zone	*tmp;
	void	*ptr;
	int		i;

	tmp = get_next_available_zone(zone, &i);
	if (!tmp)
	{
		if (!(tmp = create_zone(zone, zone->kind, size)))
			return (NULL);
	}
	tmp->allocated[i] = 1;
	tmp->areas_left--;
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
			if (!(g_data.tiny = create_zone(NULL, TINY, g_data.tiny_size)))
				return (NULL);
		return (allocate_memory(g_data.tiny, g_data.tiny_size));
	}
	else if (size <= g_data.small_coeff)
	{
		if (!g_data.small)
			if (!(g_data.small = create_zone(NULL, SMALL, g_data.small_size)))
				return (NULL);
		return (allocate_memory(g_data.small, g_data.small_size));
	}
	if (!g_data.large)
		if (!(g_data.large = create_zone(NULL, LARGE, size)))
			return (NULL);
	return (allocate_memory(g_data.large, size));
}
