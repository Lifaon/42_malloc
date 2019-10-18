/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:29:17 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/18 16:01:10 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

static t_zone	*match_large_ptr(t_zone *zone, void *ptr)
{
	t_zone	*tmp;

	if (zone == NULL)
		return (NULL);
	tmp = zone;
	while (1)
	{
		if (tmp->ptr == ptr)
			return (tmp);
		tmp = tmp->next;
		if (tmp->is_root)
			break ;
	}
	return (NULL);
}

static t_zone	*match_tiny_small_ptr(t_zone *zone, void *ptr, int *i)
{
	t_zone	*tmp;
	size_t	coeff;

	if (zone == NULL)
		return (NULL);
	tmp = zone;
	coeff = zone->kind == TINY ? g_data.tiny_coeff : g_data.small_coeff;
	while (1)
	{
		if (tmp->areas_left != zone->limit &&
			tmp->ptr <= ptr && (tmp->ptr + coeff * tmp->limit) > ptr)
		{
			*i = -1;
			while (++(*i) < zone->limit)
				if (tmp->allocated[*i] && ((tmp->ptr + (coeff * *i)) == ptr))
					return (tmp);
		}
		tmp = tmp->next;
		if (tmp->is_root)
			break ;
	}
	return (NULL);
}

t_zone			*match_ptr(t_zone *zone, void *ptr, int *i)
{
	if (zone == NULL)
		return (NULL);
	if (zone->kind == LARGE)
		return (match_large_ptr(zone, ptr));
	return (match_tiny_small_ptr(zone, ptr, i));
}

void			match_zone_ptr(t_zone **zone, void *ptr, int *i)
{
	*i = 0;
	*zone = match_large_ptr(g_data.large, ptr);
	if (!(*zone))
		*zone = match_tiny_small_ptr(g_data.small, ptr, i);
	if (!(*zone))
		*zone = match_tiny_small_ptr(g_data.tiny, ptr, i);
}
