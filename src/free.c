/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:36:00 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/18 16:08:19 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "mymalloc.h"
#include "ft_printf.h"

void	free_zone(t_zone *zone, t_zone **g_data_ptr)
{
	munmap(zone->ptr, zone->size);
	if (zone == zone->next)
		*g_data_ptr = NULL;
	else
	{
		if (zone->is_root)
		{
			zone->next->is_root = 1;
			*g_data_ptr = zone->next;
		}
		zone->prev->next = zone->next;
		zone->next->prev = zone->prev;
	}
	munmap(zone, sizeof(t_zone));
}

void	free_area(t_zone *zone, t_zone **g_data_ptr, int i)
{
	t_zone	*tmp;

	zone->allocated[i] = 0;
	zone->areas_left++;
	if (zone->areas_left == zone->limit)
	{
		tmp = zone;
		while ((tmp = tmp->next) != zone)
			if (tmp->areas_left == tmp->limit)
			{
				free_zone(zone, g_data_ptr);
				return ;
			}
	}
}

void	free(void *ptr)
{
	t_zone	*zone;
	int		i;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mtx.free);
	if ((zone = match_ptr(g_data.large, ptr, &i)))
		free_zone(zone, &g_data.large);
	else if ((zone = match_ptr(g_data.small, ptr, &i)))
		free_area(zone, &g_data.small, i);
	else if ((zone = match_ptr(g_data.tiny, ptr, &i)))
		free_area(zone, &g_data.tiny, i);
	pthread_mutex_unlock(&g_mtx.free);
}
