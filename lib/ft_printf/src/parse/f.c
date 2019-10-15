/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:43:47 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/26 20:35:40 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

static int	get_size(t_param *param, long double nb)
{
	int size;

	size = 1;
	if (param->preci == -1)
		param->preci = 6;
	size += param->preci;
	if (param->preci || param->flag.sharp)
		++size;
	if (nb < 0.0L)
		nb = -nb;
	while (nb >= 10.0L)
	{
		nb /= 10.0L;
		++size;
	}
	return (size);
}

static char	get_sign(t_param *param, long double *nb)
{
	int		*p;
	float	tmp;
	char	sign;

	sign = 0;
	if (*nb == 0.0L)
	{
		tmp = (float)(*nb);
		p = (int *)(&tmp);
		if (*p & (1 << 31))
			return ('-');
	}
	if (*nb < 0.0L)
	{
		sign = '-';
		*nb = -(*nb);
	}
	else if (param->flag.plus)
		sign = '+';
	else if (param->flag.space)
		sign = ' ';
	return (sign);
}

static void	get_size_sign(t_param *param, long double *nb, int *size, int *sign)
{
	*size = get_size(param, *nb);
	*sign = get_sign(param, nb);
	if (*sign != 0)
		++(*size);
}

static int	inf_nan(t_param *param, long double nb)
{
	int		i;
	char	buff[5];

	i = 0;
	if (nb == (1.0L / 0.0L) || nb == (-1.0L / 0.0L) || nb != nb)
	{
		if (nb == (-1.0L / 0.0L))
			buff[i++] = '-';
		buff[i++] = nb != nb ? 'n' : 'i';
		buff[i++] = nb != nb ? 'a' : 'n';
		buff[i++] = nb != nb ? 'n' : 'f';
	}
	else
		return (0);
	buff[i] = '\0';
	if (i < param->width && !param->flag.minus)
		while (i++ < param->width)
			add_char_to_buff(param, ' ');
	i = 0;
	while (buff[i])
		add_char_to_buff(param, buff[i++]);
	if (i < param->width && param->flag.minus)
		while (i++ < param->width)
			add_char_to_buff(param, ' ');
	return (1);
}

void		f(t_param *param)
{
	long double	nb;
	int			size;
	int			sign;

	if (param->size == LONG)
		nb = va_arg(param->ap, long double);
	else
		nb = (long double)va_arg(param->ap, double);
	if (inf_nan(param, nb))
		return ;
	get_size_sign(param, &nb, &size, &sign);
	if (sign && (param->width <= size || param->flag.zero || param->flag.minus))
	{
		add_char_to_buff(param, sign);
		sign = 0;
	}
	if (param->width > size && !param->flag.minus)
		while (size++ < param->width)
			add_char_to_buff(param, param->flag.zero ? '0' : ' ');
	if (sign)
		add_char_to_buff(param, sign);
	ft_dtoa(param, nb);
	if (param->width > size)
		while (size++ < param->width)
			add_char_to_buff(param, ' ');
}
