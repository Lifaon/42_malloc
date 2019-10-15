/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:42:27 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/21 21:35:10 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

void	b(t_param *param)
{
	t_ull	nb;
	char	buff[65];
	int		i;

	nb = va_arg(param->ap, t_ull);
	i = 64;
	buff[i] = '\0';
	while (i-- > 0)
	{
		buff[i] = '0' + (nb % 2);
		nb /= 2;
	}
	i = 0;
	while (buff[i])
	{
		add_char_to_buff(param, buff[i++]);
		if (i % 8 == 0 && i != 64)
			add_char_to_buff(param, ' ');
	}
}
