/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:04:21 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/28 10:16:42 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

static void	print_width(int len, char c, t_ull nb, t_param *param)
{
	int tmp;

	tmp = 2;
	if (!param->preci && !nb)
		tmp -= 1;
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

static void	add_pos(t_param *param)
{
	add_char_to_buff(param, '0');
	add_char_to_buff(param, 'x');
}

void		p(t_param *param)
{
	t_ull	nb;
	char	buff[23];
	int		len;
	int		i;

	nb = (t_ull)va_arg(param->ap, t_ull);
	ft_utoa_base(nb, 16, 0, &buff);
	len = 0;
	while (buff[len])
		++len;
	if (len < param->width && !param->flag.minus
		&& (!param->flag.zero || (param->preci >= 0)))
		print_width(len, ' ', nb, param);
	add_pos(param);
	if (len < param->width && !param->flag.minus && param->flag.zero)
		print_width(len, '0', nb, param);
	print_preci(len, param);
	i = 0;
	if (param->preci || nb)
		while (buff[i])
			add_char_to_buff(param, buff[i++]);
	if (len < param->width && param->flag.minus)
		print_width(len, ' ', nb, param);
}
