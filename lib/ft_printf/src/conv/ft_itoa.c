/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 01:01:10 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/21 21:25:48 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_nbrlen(long long nb)
{
	int len;

	len = 1;
	if (nb < 0)
	{
		nb = -nb;
		++len;
	}
	while (nb >= 10)
	{
		nb /= 10;
		++len;
	}
	return (len);
}

static void	fill_min_ll(char (*buff)[21])
{
	(*buff)[0] = '-';
	(*buff)[1] = '9';
	(*buff)[2] = '2';
	(*buff)[3] = '2';
	(*buff)[4] = '3';
	(*buff)[5] = '3';
	(*buff)[6] = '7';
	(*buff)[7] = '2';
	(*buff)[8] = '0';
	(*buff)[9] = '3';
	(*buff)[10] = '6';
	(*buff)[11] = '8';
	(*buff)[12] = '5';
	(*buff)[13] = '4';
	(*buff)[14] = '7';
	(*buff)[15] = '7';
	(*buff)[16] = '5';
	(*buff)[17] = '8';
	(*buff)[18] = '0';
	(*buff)[19] = '8';
	(*buff)[20] = '\0';
}

void		ft_itoa(long long nb, char (*buff)[21])
{
	int	len;
	int	a;

	if (nb == (-9223372036854775807 - 1))
	{
		fill_min_ll(buff);
		return ;
	}
	len = ft_nbrlen(nb);
	a = 0;
	(*buff)[len] = '\0';
	if (nb < 0)
	{
		(*buff)[0] = '-';
		nb = -nb;
		a = 1;
	}
	while (len-- > a)
	{
		(*buff)[len] = nb % 10 + '0';
		nb /= 10;
	}
}
