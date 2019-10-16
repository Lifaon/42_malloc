/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:10:44 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/16 10:56:12 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

static void	ft_memcpy(void *dst, void *src, size_t size)
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

void		*realloc(void *ptr, size_t size)
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
