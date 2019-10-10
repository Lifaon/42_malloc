/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:09:52 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/10 15:40:47 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZONE_H
# define ZONE_H

# include <stddef.h>

typedef struct		s_zone
{
	void			*ptr;
	size_t			size;
	_Bool			allocated[128];
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
