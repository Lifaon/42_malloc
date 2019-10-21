/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:08:34 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/21 18:20:10 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "mymalloc.h"

static void		*ft_mmap(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

static t_zone	*create_zone(t_zone *zone, t_kind kind, size_t size)
{
	t_zone	*new;
	int		i;

	if (!(new = (t_zone *)ft_mmap(sizeof(t_zone))))
		return (NULL);
	if (size && !(new->ptr = ft_mmap(size)))
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

static void		*allocate_memory(t_zone **zone, t_kind kind, size_t size)
{
	t_zone	*tmp;
	void	*ptr;
	int		i;

	if (!*zone && (!(*zone = create_zone(NULL, kind, size))))
		return (NULL);
	tmp = get_next_available_zone(*zone, &i);
	if (!tmp && (!(tmp = create_zone(*zone, kind, size))))
		return (NULL);
	tmp->allocated[i] = 1;
	tmp->areas_left--;
	ptr = tmp->ptr;
	if (kind == TINY)
		ptr += g_data.tiny_coeff * i;
	else if (kind == SMALL)
		ptr += g_data.small_coeff * i;
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mtx.malloc);
	if (size <= g_data.tiny_coeff)
		ptr = allocate_memory(&g_data.tiny, TINY, g_data.tiny_size);
	else if (size <= g_data.small_coeff)
		ptr = allocate_memory(&g_data.small, SMALL, g_data.small_size);
	else
		ptr = allocate_memory(&g_data.large, LARGE, size);
	pthread_mutex_unlock(&g_mtx.malloc);
	return (ptr);
}
