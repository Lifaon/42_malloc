/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 01:01:10 by mlantonn          #+#    #+#             */
/*   Updated: 2019/03/26 20:39:18 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_nbrlen(unsigned long long nb, int base)
{
	int len;

	len = 1;
	while (nb >= (unsigned long long)base)
	{
		nb /= base;
		++len;
	}
	return (len);
}

static void	init_str(char (*str)[16], int maj)
{
	int i;

	i = -1;
	while (++i < 10)
		(*str)[i] = '0' + i;
	--i;
	while (++i < 16)
		(*str)[i] = (maj ? 'A' : 'a') - 10 + i;
}

void		ft_utoa_base(unsigned long long nb, int base, int maj,
															char (*buff)[23])
{
	char	str[16];
	int		len;

	len = ft_nbrlen(nb, base);
	init_str(&str, maj);
	(*buff)[len] = '\0';
	while (len-- > 0)
	{
		(*buff)[len] = str[nb % base];
		nb /= base;
	}
}
