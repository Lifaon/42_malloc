/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_static.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:42:13 by mlantonn          #+#    #+#             */
/*   Updated: 2019/10/17 16:32:56 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ft_printf.h"

static t_param	g_param;

#define __CONSTRUCTOR	__attribute__((constructor)) static void
#define __DESTRUCTOR	__attribute__((destructor)) static void

__CONSTRUCTOR	first_init(void)
{
	init_param(&g_param, NULL);
}

__DESTRUCTOR	dump_buffer(void)
{
	print_buff(&g_param);
}

void			ft_printf_static_dump(void)
{
	print_buff(&g_param);
}

int				ft_printf_static(const char *fmt, ...)
{
	if (fmt == NULL)
		return (-1);
	g_param.fmt = (char *)fmt;
	va_start(g_param.ap, fmt);
	parse_fmt(&g_param);
	va_end(g_param.ap);
	return (g_param.buff_read);
}
