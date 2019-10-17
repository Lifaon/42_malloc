/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:31:22 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/17 11:20:37 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*arr;
	size_t	total;
	size_t	i;

	pthread_mutex_lock(&mtx.calloc);
	total = count * size;
	ptr = malloc(total);
	if (ptr)
	{
		arr = (char *)ptr;
		i = -1;
		while (++i < total)
			arr[i] = 0;
	}
	pthread_mutex_unlock(&mtx.calloc);
	return (ptr);
}
