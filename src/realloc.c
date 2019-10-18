/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:29:51 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/18 16:06:55 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

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
	size_t	zone_size;
	void	*new;
	int		i;

	pthread_mutex_lock(&g_mtx.realloc);
	new = NULL;
	match_zone_ptr(&zone, ptr, &i);
	if (zone || ptr == NULL)
		new = malloc(size);
	if (zone)
	{
		zone_size = zone->size / zone->limit;
		ft_memcpy(new, ptr, zone_size < size ? zone_size : size);
		if (zone->kind == LARGE)
			free_zone(zone, &g_data.large);
		else if (zone->kind == SMALL)
			free_area(zone, &g_data.small, i);
		else
			free_area(zone, &g_data.tiny, i);
	}
	pthread_mutex_unlock(&g_mtx.realloc);
	return (new);
}
