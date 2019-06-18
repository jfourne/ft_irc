/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:19:44 by jfourne           #+#    #+#             */
/*   Updated: 2017/02/22 14:25:47 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisalpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
