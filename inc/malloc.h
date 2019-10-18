/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:14:53 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/17 17:12:51 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem(void);
void	hexdump(void *ptr);

#endif
