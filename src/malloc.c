/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:08:34 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/10 16:54:38 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/errno.h>
#include "zone.h"

#include <stdio.h>

static t_zone	*get_next_available_zone(t_zone *zone, int *i)
{
	t_zone	*tmp;

	tmp = zone;
	while (tmp)
	{
		*i = -1;
		while (++(*i) < 128)
			if (!tmp->allocated[*i])
				return (tmp);
		tmp = tmp->next;
	}
	*i = 0;
	return (NULL);
}

static t_zone	*create_zone(size_t size)
{
	t_zone	*zone;
	int		i;

	zone = (t_zone *)mmap(NULL, sizeof(t_zone), PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zone)
		return (zone);
	zone->ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zone->ptr)
	{
		munmap(zone, sizeof(t_zone));
		return (zone);
	}
	zone->size = size;
	i = -1;
	while (++i < 128)
		zone->allocated[i] = 0;
	zone->next = NULL;
	return (zone);
}

static void		*tiny_alloc(void)
{
	t_zone	*tmp;
	int		i;

	if (!g_data.tiny)
		if (!(g_data.tiny = create_zone(g_data.tiny_size)))
			return (NULL);
	tmp = get_next_available_zone(g_data.tiny, &i);
	if (!tmp)
	{
		tmp = g_data.tiny;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = create_zone(g_data.tiny_size)))
			return (NULL);
		tmp = tmp->next;
	}
	tmp->allocated[i] = 1;
	return (tmp->ptr + (g_data.tiny_coeff * i));
}

void			*malloc(size_t size)
{
	void	*ptr;
	(void)size;
	ptr = tiny_alloc();
	return (ptr);
}

// 32 / 
