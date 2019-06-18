/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 12:49:00 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/27 14:26:36 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static void		my_itoa_base(uint64_t n, uint64_t count,
								char *base, char *str)
{
	uint64_t			base_nb;

	base_nb = ft_strlen(base);
	if ((n / base_nb) == 0)
	{
		while (count > 1)
		{
			*str = base[0];
			count /= base_nb;
			str++;
		}
		*str = base[n];
		*(str + 1) = '\0';
		return ;
	}
	*str = base[n / count];
	my_itoa_base(n % count, count / base_nb, base, str + 1);
}

char			*ft_itoa_base(uint64_t n, char *base)
{
	uint64_t			count;
	uint64_t			base_nb;
	char				*str;

	if ((str = (char *)malloc(512 * sizeof(char))) == NULL)
		return (NULL);
	base_nb = ft_strlen(base);
	count = base_nb;
	while ((base_nb < ULLONG_MAX / count) && count * base_nb <= n)
	{
		if (count == 0)
			return (NULL);
		count *= base_nb;
	}
	my_itoa_base(n, count, base, str);
	return (str);
}
