/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:49:32 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/21 18:10:49 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include "mymalloc.h"

__CONSTRUCTOR	init_g_data(void)
{
	g_data.page_size = getpagesize();
	g_data.tiny = NULL;
	g_data.tiny_size = g_data.page_size;
	g_data.tiny_coeff = g_data.tiny_size / 128;
	g_data.small = NULL;
	g_data.small_size = g_data.page_size * 32;
	g_data.small_coeff = g_data.small_size / 128;
	g_data.large = NULL;
}

static void		free_whole_zone(t_zone *zone)
{
	t_zone	*tmp;
	t_zone	*next;

	if (zone == NULL)
		return ;
	next = zone->next;
	while (!next->is_root)
	{
		tmp = next;
		next = next->next;
		munmap(tmp->ptr, tmp->size);
		munmap(tmp, sizeof(t_zone));
	}
	munmap(zone->ptr, zone->size);
	munmap(zone, sizeof(t_zone));
}

__DESTRUCTOR	free_g_data(void)
{
	free_whole_zone(g_data.tiny);
	free_whole_zone(g_data.small);
	free_whole_zone(g_data.large);
}
