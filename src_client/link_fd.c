/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:00:08 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:12:46 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			link_fd(t_client *me)
{
	if (me->socket > 0)
		me->max_fd = me->socket;
	FD_ZERO(&me->fd_read);
	FD_ZERO(&me->fd_write);
	FD_SET(0, &me->fd_read);
	if (me->socket != 0)
		FD_SET(me->socket, &me->fd_read);
}
