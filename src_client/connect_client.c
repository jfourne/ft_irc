/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:13:23 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/10 12:02:28 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void					try_connection(struct addrinfo *res, t_client *me)
{
	struct addrinfo		*save_res;

	while (res != NULL)
	{
		save_res = res;
		me->connected = connect(me->socket, res->ai_addr, res->ai_addrlen);
		res = res->ai_next;
		free(save_res->ai_addr);
		free(save_res);
	}
	if (res)
		free(res);
}

int						connect_client(const char *machine, char *port_str,
							struct addrinfo hints, t_client *me)
{
	int					ret;
	struct addrinfo		*res;
	struct protoent		*pe;

	res = NULL;
	ret = EXIT_SUCCESS;
	pe = (struct protoent*)getprotobyname("tcp");
	if (getaddrinfo(machine, port_str, &hints, &res) != 0)
		return (error("getaddrinfo", "error"));
	if ((me->socket = socket(hints.ai_family, hints.ai_socktype,
								pe->p_proto)) == -1)
		return (error("socket", "can't create a scoket"));
	try_connection(res, me);
	if (me->connected == FALSE)
		return (error("connect", "couldn't connect to server"));
	ft_putstr("You're now connected to ");
	ft_putstr(machine);
	ft_putchar('\n');
	return (ret);
}
