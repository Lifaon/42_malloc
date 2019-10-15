/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:44:10 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/21 21:43:28 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H

# include "structs.h"

void		add_char_to_buff(t_param *param, char c);

long long	ft_atoi(char const *str);
void		ft_itoa(long long nb, char (*buff)[21]);
void		ft_utoa_base(t_ull nb, int base, int maj, char (*buff)[23]);
void		ft_dtoa(t_param *param, long double nb);

#endif
