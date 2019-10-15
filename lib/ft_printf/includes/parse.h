/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:44:10 by mlantonn          #+#    #+#             */
/*   Updated: 2019/06/12 18:43:34 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdarg.h>
# include "structs.h"

void	print_type(t_param *param);
void	c(t_param *param);
void	s(t_param *param);
void	p(t_param *param);
void	i(t_param *param);
void	o(t_param *param);
void	u(t_param *param);
void	x(t_param *param);
void	f(t_param *param);
void	b(t_param *param);

#endif
