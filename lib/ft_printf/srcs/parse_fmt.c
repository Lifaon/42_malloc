/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:00:00 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/23 23:32:04 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	find_flag(t_param *param, char c)
{
	if (c == '#')
		param->flag.sharp = TRUE;
	else if (c == '0')
		param->flag.zero = TRUE;
	else if (c == '-')
		param->flag.minus = TRUE;
	else if (c == '+')
		param->flag.plus = TRUE;
	else if (c == ' ')
		param->flag.space = TRUE;
	else
		return (0);
	return (1);
}

static void	find_width_preci(t_param *param)
{
	if (*param->fmt >= '1' && *param->fmt <= '9')
		param->width = ft_atoi(param->fmt);
	else if (*param->fmt == '*')
	{
		param->width = va_arg(param->ap, long long);
		param->fmt++;
	}
	while (*param->fmt >= '0' && *param->fmt <= '9')
		param->fmt++;
	if (*param->fmt == '.')
	{
		param->fmt++;
		param->preci = 0;
		if (*param->fmt >= '0' && *param->fmt <= '9')
			param->preci = ft_atoi(param->fmt);
		else if (*param->fmt == '*')
		{
			param->preci = va_arg(param->ap, long long);
			param->fmt++;
		}
		while (*param->fmt >= '0' && *param->fmt <= '9')
			param->fmt++;
	}
}

static void	find_type(t_param *param)
{
	static t_ptr	funcptr[127] = {NULL};
	char			size;

	init_func(funcptr);
	size = 0;
	if (*param->fmt == 'h' || *param->fmt == 'l' || *param->fmt == 'L')
	{
		param->size = *(param->fmt++) == 'h' ? SHORT : LONG;
		size = param->size;
		if ((*param->fmt == 'h' && param->size == SHORT)
		|| (*param->fmt == 'l' && param->size == LONG))
			param->size = *(param->fmt++) == 'h' ? SHORTCHAR : LONGLONG;
	}
	param->type = (int)(*param->fmt);
	if (size == 'l' && param->type == 'f')
		param->size = 0;
	funcptr[(int)(*param->fmt++)](param);
}

void		parse_fmt(t_param *param)
{
	while (*param->fmt)
	{
		if (*param->fmt != '%')
			add_char_to_buff(param, *(param->fmt++));
		else
		{
			param->flag.sharp = FALSE;
			param->flag.zero = FALSE;
			param->flag.minus = FALSE;
			param->flag.plus = FALSE;
			param->flag.space = FALSE;
			param->width = 0;
			param->preci = -1;
			param->size = 0;
			param->fmt++;
			while (find_flag(param, *param->fmt))
				param->fmt++;
			find_width_preci(param);
			find_type(param);
		}
	}
}

void		print_fmt(t_param *param)
{
	parse_fmt(param);
	print_buff(param);
}
