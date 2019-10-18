/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:45:56 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/18 11:19:04 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"
#include "ft_printf.h"

static void	print_end_of_line(void *ptr)
{
	char	buff[17];
	char	*str;
	int		i;

	str = (char *)ptr;
	i = -1;
	while (++i < 16)
	{
		if (str[i] > 31 && str[i] < 127)
			buff[i] = str[i];
		else
			buff[i] = '.';
	}
	buff[i] = '\0';
	ft_printf_static("|%s|\n", buff);
}

static void	print_dump(void *ptr, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		if (!(i % 16))
			ft_printf_static("%.8x  ", i);
		ft_printf_static("%.2x", *(unsigned char *)(ptr + i));
		ft_printf_static(" ");
		if (!((i + 1) % 8))
			ft_printf_static(" ");
		if (!((i + 1) % 16))
			print_end_of_line(ptr + (i - 15));
	}
	if (i % 16)
	{
		ft_printf_static("%*s", (1 + (i % 16 < 8) + 3 * (16 - (i % 16))), "");
		i += 16 - (i % 16);
		print_end_of_line(ptr + i - 16);
	}
	ft_printf_static("%.8x\n", i);
	ft_printf_static_dump();
}

void		hexdump(void *ptr)
{
	t_zone	*zone;
	int		i;

	match_zone_ptr(&zone, ptr, &i);
	if (!zone)
		ft_printf("hexdump: pointer not found: %p\n", ptr);
	else
		print_dump(ptr, zone->size / zone->limit);
}
