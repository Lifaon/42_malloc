/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_mtx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:43:16 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/17 11:02:31 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

__CONSTRUCTOR	init_g_mtx(void)
{
	pthread_mutex_init(&g_mtx.malloc, NULL);
	pthread_mutex_init(&g_mtx.calloc, NULL);
	pthread_mutex_init(&g_mtx.realloc, NULL);
	pthread_mutex_init(&g_mtx.free, NULL);
	pthread_mutex_init(&g_mtx.show_alloc_mem, NULL);
}

__DESTRUCTOR	free_g_mtx(void)
{
	pthread_mutex_destroy(&g_mtx.malloc);
	pthread_mutex_destroy(&g_mtx.calloc);
	pthread_mutex_destroy(&g_mtx.realloc);
	pthread_mutex_destroy(&g_mtx.free);
	pthread_mutex_destroy(&g_mtx.show_alloc_mem);
}
