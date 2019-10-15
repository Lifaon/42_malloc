/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:46:36 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/21 21:25:46 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoi(char const *str)
{
	long long nb;
	long long sign;

	nb = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		++str;
	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
		nb = nb * 10 + (*str++ - '0');
	if (nb < 0)
	{
		nb = 9223372036854775807;
		return (sign == 1 ? nb : nb + 1);
	}
	return (nb * sign);
}
