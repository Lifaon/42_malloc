/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:42:37 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/26 20:36:23 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"

static void	print_null(t_param *param, int len)
{
	if (!len)
		return ;
	add_char_to_buff(param, '(');
	add_char_to_buff(param, 'n');
	add_char_to_buff(param, 'u');
	add_char_to_buff(param, 'l');
	add_char_to_buff(param, 'l');
	add_char_to_buff(param, ')');
}

void		s(t_param *param)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	str = va_arg(param->ap, char *);
	if (str == NULL)
		len = param->preci ? 6 : 0;
	else
		while (str[len])
			++len;
	if (param->preci >= 0 && len > param->preci)
		len = param->preci;
	if (len < param->width && !param->flag.minus)
		while (len++ < param->width)
			add_char_to_buff(param, ' ');
	if (str == NULL)
		print_null(param, len);
	else
		while (str[i] && (param->preci == -1 || i < param->preci))
			add_char_to_buff(param, str[i++]);
	if (len < param->width && param->flag.minus)
		while (len++ < param->width)
			add_char_to_buff(param, ' ');
}
