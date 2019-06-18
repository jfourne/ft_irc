/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:33:17 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:12:44 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			buff_word_end(t_circle_buf *buffer)
{
	buffer->wbegin = buffer->wcurr;
	buffer->wcurr_len = 0;
}

int				init_buffer(t_circle_buf *buffer)
{
	if ((buffer->tab = (char *)malloc(sizeof(char) * BUFF_SIZE)) == NULL)
		return (error("malloc", "can't allocate new memory"));
	ft_bzero(buffer->tab, BUFF_SIZE);
	buffer->end = buffer->tab + BUFF_SIZE;
	buffer->wcurr_len = 0;
	buffer->wbegin = buffer->tab;
	buffer->wcurr = buffer->tab;
	return (EXIT_SUCCESS);
}
