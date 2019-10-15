/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:00:00 by mlantonn          #+#    #+#             */
/*   Updated: 2019/06/12 18:42:01 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ft_printf.h"

int		ft_printf(const char *fmt, ...)
{
	t_param	param;

	if (fmt == NULL)
		return (-1);
	init_param(&param, fmt);
	va_start(param.ap, fmt);
	print_fmt(&param);
	va_end(param.ap);
	return (param.buff_read);
}

int		ft_dprintf(int fd, const char *fmt, ...)
{
	t_param	param;

	if (fmt == NULL)
		return (-1);
	init_param(&param, fmt);
	param.fd = fd;
	va_start(param.ap, fmt);
	print_fmt(&param);
	va_end(param.ap);
	return (param.buff_read);
}

int		ft_sprintf(char *str, const char *fmt, ...)
{
	t_param	param;

	if (fmt == NULL)
		return (-1);
	init_param(&param, fmt);
	param.str = str;
	va_start(param.ap, fmt);
	print_fmt(&param);
	va_end(param.ap);
	return (param.buff_read);
}

int		ft_smprintf(char **str, const char *fmt, ...)
{
	t_param	param;
	int		size;

	if (fmt == NULL || str == NULL)
		return (-1);
	va_start(param.ap, fmt);
	size = ft_vdprintf(-1, fmt, param.ap);
	va_end(param.ap);
	*str = (char *)malloc(sizeof(char) * (size + 1));
	if (*str == NULL)
		return (-1);
	va_start(param.ap, fmt);
	init_param(&param, fmt);
	param.str = *str;
	print_fmt(&param);
	va_end(param.ap);
	return (param.buff_read);
}

int		ft_snprintf(char *str, size_t size, const char *fmt, ...)
{
	t_param	param;

	if (fmt == NULL)
		return (-1);
	init_param(&param, fmt);
	param.str = str;
	param.buff_max = size;
	param.is_maxed = TRUE;
	va_start(param.ap, fmt);
	print_fmt(&param);
	va_end(param.ap);
	return (param.buff_read);
}
