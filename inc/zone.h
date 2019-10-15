/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:09:52 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/15 15:09:19 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZONE_H
# define ZONE_H

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
	_Bool			is_root;
	size_t			size;
	_Bool			allocated[128];
	int				areas_left;
	int				limit;
	struct s_zone	*prev;
	struct s_zone	*next;
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

t_data	g_data;

#endif
