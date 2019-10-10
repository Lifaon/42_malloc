/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:49:32 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/10 16:59:03 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include "zone.h"

#define __CONSTRUCTOR	__attribute__((constructor)) static void
#define __DESTRUCTOR	__attribute__((destructor)) static void

__CONSTRUCTOR	init_data(void)
{
	g_data.page_size = getpagesize();
	g_data.tiny = NULL;
	g_data.tiny_size = g_data.page_size;
	g_data.tiny_coeff = g_data.tiny_size / 128;
	g_data.small = NULL;
	g_data.small_size = g_data.tiny_size * 16;
	g_data.small_coeff = g_data.small_size / 128;
	g_data.large = NULL;
}

__DESTRUCTOR	free_data(void)
{
	t_zone	*tmp;

	while (g_data.tiny)
	{
		tmp = g_data.tiny;
		munmap(tmp->ptr, tmp->size);
		g_data.tiny = g_data.tiny->next;
		munmap(tmp, sizeof(tmp));
	}
	while (g_data.small)
	{
		tmp = g_data.small;
		munmap(tmp->ptr, tmp->size);
		g_data.small = g_data.small->next;
		munmap(tmp, sizeof(tmp));
	}
	while (g_data.large)
	{
		tmp = g_data.large;
		munmap(tmp->ptr, tmp->size);
		g_data.large = g_data.large->next;
		munmap(tmp, sizeof(t_zone));
	}
}
