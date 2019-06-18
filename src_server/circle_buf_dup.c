/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_buf_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:58:22 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:18:05 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char			*circle_buf_dup(t_circle_buf *buffer)
{
	int			i;
	char		*buff_i;
	char		*new_s;

	if (buffer->wcurr_len == 0)
		return (NULL);
	if ((new_s = (char *)malloc(sizeof(char) * buffer->wcurr_len + 1)) == NULL)
	{
		error("malloc", "can't allocate new memory");
		return (NULL);
	}
	i = 0;
	buff_i = buffer->wbegin;
	while (buff_i != buffer->wcurr)
	{
		new_s[i] = *buff_i;
		i++;
		buff_i++;
		if (buff_i == buffer->end)
			buff_i = buffer->tab;
	}
	new_s[i] = '\0';
	return (new_s);
}
