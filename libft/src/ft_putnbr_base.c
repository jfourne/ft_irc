/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 12:49:00 by jfourne           #+#    #+#             */
/*   Updated: 2018/11/06 11:25:09 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		my_putnbr_base(int n, int count, int base_nb, char *base)
{
	if ((n / base_nb) == 0)
	{
		while (count > 1)
		{
			ft_putchar('0');
			count /= base_nb;
		}
		ft_putchar(base[n]);
		return ;
	}
	ft_putchar(base[n / count]);
	my_putnbr_base(n % count, count / base_nb, base_nb, base);
}

void			ft_putnbr_base(int n, char *base)
{
	int			neg;
	int			count;
	int			base_nb;

	neg = 0;
	base_nb = ft_strlen(base);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			neg++;
			n++;
		}
		n *= -1;
		ft_putchar('-');
	}
	count = base_nb;
	while (count * base_nb < n)
	{
		if (count == 0)
			return ;
		count *= base_nb;
	}
	my_putnbr_base(n, count, base_nb, base);
}
