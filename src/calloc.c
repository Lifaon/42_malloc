/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:31:22 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/16 13:34:32 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*arr;
	size_t	total;
	size_t	i;

	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	arr = (char *)ptr;
	i = -1;
	while (++i < total)
		arr[i] = 0;
	return (ptr);
}
