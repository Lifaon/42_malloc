/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:43:47 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/26 15:04:44 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

static void	get_sized_param(t_ull *nb, t_param *param)
{
	if (param->size == SHORTCHAR)
		*nb = (t_ull)(unsigned char)va_arg(param->ap, unsigned int);
	else if (param->size == SHORT)
		*nb = (t_ull)(unsigned short)va_arg(param->ap, unsigned int);
	else if (param->size == LONG)
		*nb = (t_ull)va_arg(param->ap, unsigned long);
	else if (param->size == LONGLONG)
		*nb = (t_ull)va_arg(param->ap, t_ull);
	else
		*nb = (t_ull)va_arg(param->ap, unsigned int);
}

static void	print_width_preci(int len, int prec_flag, t_ull nb, t_param *param)
{
	int		preci;
	int		tmp;

	preci = param->preci || nb ? 0 : -1;
	if (param->preci >= 0 && len < param->preci)
		preci = param->preci - len;
	tmp = preci;
	if (prec_flag && !param->flag.minus && len + preci < param->width)
		while (len + preci < param->width)
		{
			++len;
			add_char_to_buff(param, param->preci < 0 \
				&& param->flag.zero ? '0' : ' ');
		}
	while (prec_flag && tmp > 0)
	{
		--tmp;
		add_char_to_buff(param, '0');
	}
	if (!prec_flag && param->flag.minus && len + preci < param->width)
		while (len + preci < param->width)
		{
			++len;
			add_char_to_buff(param, ' ');
		}
}

void		u(t_param *param)
{
	t_ull	nb;
	char	buff[23];
	int		len;
	int		i;

	get_sized_param(&nb, param);
	ft_utoa_base(nb, 10, 0, &buff);
	len = 0;
	while (buff[len])
		++len;
	print_width_preci(len, 1, nb, param);
	i = 0;
	if (param->preci || nb)
		while (buff[i])
			add_char_to_buff(param, buff[i++]);
	print_width_preci(len, 0, nb, param);
}
