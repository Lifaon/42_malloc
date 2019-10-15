/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:00:00 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/23 23:31:30 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"

void	init_func(t_ptr func[127])
{
	int index;

	if (func[0] != NULL)
		return ;
	index = -1;
	while (++index < 127)
		func[index] = print_type;
	func['c'] = c;
	func['s'] = s;
	func['p'] = p;
	func['d'] = i;
	func['i'] = i;
	func['u'] = u;
	func['o'] = o;
	func['x'] = x;
	func['X'] = x;
	func['f'] = f;
	func['b'] = b;
}

void	init_param(t_param *param, const char *fmt)
{
	param->fmt = (char *)fmt;
	param->str = NULL;
	param->fd = 1;
	param->buff_len = 0;
	param->buff_read = 0;
	param->buff_max = 0;
	param->is_maxed = FALSE;
}
