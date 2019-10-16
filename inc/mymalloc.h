/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:09:52 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/16 11:08:22 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMALLOC_H
# define MYMALLOC_H

# include <stddef.h>

typedef enum		e_kind
{
	TINY,
	SMALL,
	LARGE
}					t_kind;

typedef struct		s_zone
{
	void			*ptr;
	t_kind			kind;
	size_t			size;
	_Bool			allocated[128];
	int				areas_left;
	int				limit;
	struct s_zone	*prev;
	struct s_zone	*next;
	_Bool			is_root;
}					t_zone;

typedef struct		s_data
{
	size_t			page_size;
	t_zone			*tiny;
	size_t			tiny_size;
	size_t			tiny_coeff;
	t_zone			*small;
	size_t			small_size;
	size_t			small_coeff;
	t_zone			*large;
}					t_data;

t_data				g_data;

void				*malloc(size_t size);

#endif
