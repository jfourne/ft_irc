/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_buf_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:08:40 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:12:36 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			circle_buf_cmp(char *str, t_circle_buf *buffer)
{
	int		i;
	char	*buff_i;

	i = 0;
	buff_i = buffer->wbegin;
	while (str && str[i])
	{
		if (str[i] != *buff_i)
			return (EXIT_FAILURE);
		i++;
		buff_i++;
		if (buff_i == buffer->end)
			buff_i = buffer->tab;
	}
	return (EXIT_SUCCESS);
}
