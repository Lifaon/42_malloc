/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:36:00 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/16 11:07:34 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "mymalloc.h"

static t_zone	*match_ptr(t_zone *zone, void *ptr, int *i)
{
	t_zone	*tmp;
	size_t	coeff;

	if (zone == NULL)
		return (NULL);
	tmp = zone;
	coeff = zone->kind == TINY ? g_data.tiny_coeff : g_data.small_coeff;
	while (1)
	{
		if (tmp->areas_left != zone->limit)
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

static void		free_area(t_zone *zone, t_zone **g_data_ptr, int i)
{
	zone->allocated[i] = 0;
	zone->areas_left++;
	if (zone->areas_left == zone->limit)
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
}

void			free(void *ptr)
{
	t_zone	*zone;
	int		i;

	if (!ptr)
		return ;
	if ((zone = match_ptr(g_data.tiny, ptr, &i)))
		free_area(zone, &g_data.tiny, i);
	else if ((zone = match_ptr(g_data.small, ptr, &i)))
		free_area(zone, &g_data.small, i);
	else if ((zone = match_ptr(g_data.large, ptr, &i)))
		free_area(zone, &g_data.large, i);
}

static void		ft_memcpy(void *dst, void *src, size_t size)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	if (!dst || !src)
		return ;
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	i = -1;
	while (++i < size)
		p1[i] = p2[i];
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	void	*new;
	int		i;

	i = 0;
	zone = match_ptr(g_data.tiny, ptr, &i);
	if (!zone)
		zone = match_ptr(g_data.small, ptr, &i);
	if (!zone)
		zone = match_ptr(g_data.large, ptr, &i);
	new = malloc(size);
	if (!zone)
		return (new);
	ft_memcpy(new, ptr, zone->size < size ? zone->size : size);
	if (zone->kind == TINY)
		free_area(zone, &g_data.tiny, i);
	else if (zone->kind == SMALL)
		free_area(zone, &g_data.small, i);
	else
		free_area(zone, &g_data.large, i);
	return (new);
}
