/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:42:27 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/25 11:32:49 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

void	c(t_param *param)
{
	char	c;
	int		i;

	c = (char)va_arg(param->ap, int);
	i = 1;
	if (!param->flag.minus && param->width > 1)
		while (i++ < param->width)
			add_char_to_buff(param, ' ');
	add_char_to_buff(param, c);
	if (param->flag.minus && param->width > 1)
		while (i++ < param->width)
			add_char_to_buff(param, ' ');
}
