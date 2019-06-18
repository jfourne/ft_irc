/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_create_ipv6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:12:52 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/10 10:54:52 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int						srv_create_ipv6(t_env *e, int port)
{
	struct sockaddr_in6	sin;
	struct protoent		*pe;

	if (port < 1030 || port > 65535)
		return (error("port", "must be between 1030 and 65535"));
	if ((pe = (struct protoent *)getprotobyname("tcp")) == NULL)
		return (EXIT_FAILURE);
	if ((e->s = socket(AF_INET6, SOCK_STREAM, pe->p_proto)) == -1)
		return (error("socket", "couldn't create"));
	sin.sin6_family = AF_INET6;
	sin.sin6_addr = in6addr_any;
	sin.sin6_port = htons(port);
	if (bind(e->s, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (error("bind", "couldn't bind"));
	if (listen(e->s, 42) == -1)
		return (error("listen", "couldn't listen"));
	e->fds[e->s].type = FD_SERV;
	e->fds[e->s].fct_read = srv_accept;
	return (EXIT_SUCCESS);
}
