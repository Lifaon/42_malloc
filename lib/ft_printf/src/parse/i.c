/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:43:50 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/27 11:46:16 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

static void	get_sized_param(long long *nb, t_param *param)
{
	if (param->size == SHORTCHAR)
		*nb = (long long)(char)va_arg(param->ap, int);
	else if (param->size == SHORT)
		*nb = (long long)(short)va_arg(param->ap, int);
	else if (param->size == LONG)
		*nb = (long long)va_arg(param->ap, long);
	else if (param->size == LONGLONG)
		*nb = (long long)va_arg(param->ap, long long);
	else
		*nb = (long long)va_arg(param->ap, int);
}

static void	print_width(int len, char c, long long nb, t_param *param)
{
	int tmp;

	tmp = param->preci || nb ? 0 : -1;
	if (nb < 0)
	{
		if (param->preci >= len)
			tmp += 1;
	}
	else if (param->flag.plus || param->flag.space)
		tmp += 1;
	if (param->preci >= 0 && len < param->preci)
		tmp += param->preci - len;
	if (len + tmp < param->width)
	{
		while (len + tmp < param->width)
		{
			++len;
			add_char_to_buff(param, c);
		}
		if (len + tmp == param->width)
			param->width = 0;
	}
}

static void	print_preci(int len, t_param *param)
{
	if (param->preci >= 0)
		while (len < param->preci)
		{
			++len;
			add_char_to_buff(param, '0');
		}
}

static void	add_pos(t_param *param, long long nb)
{
	if (nb >= 0)
	{
		if (param->flag.plus)
			add_char_to_buff(param, '+');
		else if (param->flag.space)
			add_char_to_buff(param, ' ');
	}
	else
		add_char_to_buff(param, '-');
}

void		i(t_param *param)
{
	long long	nb;
	char		buff[21];
	int			len;
	int			i;

	get_sized_param(&nb, param);
	ft_itoa(nb, &buff);
	len = 0;
	while (buff[len])
		++len;
	if (!param->flag.minus && (!param->flag.zero || (param->preci >= 0)))
		print_width(len, ' ', nb, param);
	add_pos(param, nb);
	if (!param->flag.minus && param->flag.zero)
		print_width(len, '0', nb, param);
	print_preci(len - (nb < 0), param);
	i = (nb < 0);
	if (param->preci || nb)
		while (buff[i])
			add_char_to_buff(param, buff[i++]);
	if (param->flag.minus)
		print_width(len, ' ', nb, param);
}
