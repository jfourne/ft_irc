/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:26:40 by jfourne           #+#    #+#             */
/*   Updated: 2018/11/09 11:46:30 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				swap_bytes(unsigned char *bytes, int size)
{
	int				i;
	int				j;
	unsigned char	tmp;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		tmp = bytes[i];
		bytes[i] = bytes[j];
		bytes[j] = tmp;
		i++;
		j--;
	}
}
