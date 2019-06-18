/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:58:43 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:13:48 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			send_to_server(t_client *me)
{
	int			well_send;
	int			msg_len;
	char		*new_str;
	char		*save_str;

	if ((new_str = circle_buf_dup(me->buff_read)) == NULL)
		return ;
	well_send = 0;
	msg_len = ft_strlen(new_str);
	save_str = new_str;
	while (msg_len > 0 && well_send != -1)
	{
		well_send = send(me->socket, new_str, msg_len, 0);
		new_str += well_send;
		msg_len -= well_send;
	}
	free(save_str);
}
