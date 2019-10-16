/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:03:49 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/16 12:06:57 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"
#include "ft_printf.h"

static void	show_zone(t_zone *zone, size_t	coeff)
{
	int	i;
	int	start;
	int	at_limit;

	i = -1;
	start = 0;
	while (++i < zone->limit)
	{
		at_limit = i == zone->limit - 1;
		if (!zone->allocated[i] || at_limit)
		{
			if (start != -1)
			{
				ft_printf("  %p - %p : %lu bytes\n",
					zone->ptr + (coeff * start),
					zone->ptr + (coeff * (i + at_limit)),
					coeff * (i + at_limit - start));
			}
		}
		if (!zone->allocated[i])
			start = -1;
		else if (start == -1)
		{
			ft_printf("chelou\n");
			start = i;
		}
	}
}

static void	show_whole_zone(t_zone *zone, t_kind kind)
{
	static char	kinds[3][10] = {"TINY", "SMALL", "LARGE"};
	size_t		coeff;

	if (!zone)
	{
		ft_printf("%s:\tno allocation\n", kinds[kind]);
		return ;
	}
	coeff = zone->size;
	if (kind == TINY)
		coeff = g_data.tiny_coeff;
	if (kind == SMALL)
		coeff = g_data.small_coeff;
	while (1)
	{
		ft_printf("%s:\t%p\n", kinds[kind], zone->ptr);
		show_zone(zone, coeff);
		zone = zone->next;
		if (zone->is_root)
			break ;
	}
}

void		show_alloc_mem(void)
{
	show_whole_zone(g_data.tiny, TINY);
	show_whole_zone(g_data.small, SMALL);
	show_whole_zone(g_data.large, LARGE);
	ft_printf("\n");
}
