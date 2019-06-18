/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:43:52 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:12:45 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			leave_server(t_client *me)
{
	if (me->connected == FALSE)
	{
		error("leave", "You're not on a server");
		return ;
	}
	me->connected = FALSE;
	if (me->socket != 0)
		close(me->socket);
	FD_CLR(me->socket, &me->fd_read);
	me->socket = 0;
	ft_putstr("You left the server\n");
}
