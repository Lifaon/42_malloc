/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 21:29:01 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/26 15:07:26 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

static long double	ft_10pow(int n)
{
	long double nb;

	nb = 1.0L;
	if (n > 0)
		while (n-- > 0)
			nb *= 10.0L;
	else if (n < 0)
		while (n++ < 0)
			nb /= 10.0L;
	return (nb);
}

static void			ft_utoa(t_param *param, t_ull nb, int scale)
{
	t_ull	tmp;
	char	buff[20];
	int		len;
	int		i;

	len = 1;
	tmp = nb;
	while (tmp >= 10)
	{
		tmp /= 10;
		++len;
	}
	i = 0;
	while (len + i++ < scale)
		add_char_to_buff(param, '0');
	buff[len] = '\0';
	while (len > 0)
	{
		buff[--len] = '0' + nb % 10;
		nb /= 10;
	}
	while (buff[len])
		add_char_to_buff(param, buff[len++]);
}

static void			add_mantissa(t_param *param, long double nb)
{
	int	scale;
	int	i;
	int	j;

	i = 0;
	scale = 19;
	while (i < param->preci)
	{
		if (i + scale >= param->preci)
		{
			scale = param->preci - i;
			nb += 0.5L * ft_10pow(-scale);
		}
		i += scale;
		ft_utoa(param, (t_ull)(nb * ft_10pow(scale)), scale);
		j = 0;
		while (j++ < scale)
		{
			nb *= 10.0L;
			nb -= (long double)(char)nb;
		}
	}
}

static void			add_integer(t_param *param, long double *nb)
{
	long double tmp;
	long double	tenpow;
	char		digit;
	int			scale;

	scale = 1;
	tmp = *nb;
	while (tmp >= 10.0L)
	{
		tmp /= 10.0L;
		++scale;
	}
	while (scale-- > 0)
	{
		tenpow = ft_10pow(scale);
		digit = (char)(*nb / tenpow);
		add_char_to_buff(param, '0' + digit);
		*nb -= tenpow * (long double)digit;
	}
}

void				ft_dtoa(t_param *param, long double nb)
{
	if (param->preci == 0)
		nb += 0.4999L;
	add_integer(param, &nb);
	if (param->preci || param->flag.sharp)
		add_char_to_buff(param, '.');
	add_mantissa(param, nb);
}
