/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:19:57 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:12:33 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			add_to_buffer(t_circle_buf *buffer, char buf)
{
	*(buffer->wcurr) = buf;
	buffer->wcurr += 1;
	buffer->wcurr_len++;
	if (buffer->wcurr == buffer->end)
		buffer->wcurr = buffer->tab;
}
