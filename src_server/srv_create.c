/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:56:44 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 16:10:35 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int						srv_create(t_env *e, int port)
{
	struct sockaddr_in	sin;
	struct protoent		*pe;

	if (port < 1030 || port > 65535)
		return (error("port", "must be between 1030 and 65535"));
	if ((pe = (struct protoent *)getprotobyname("tcp")) == NULL)
		return (EXIT_FAILURE);
	if ((e->s = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		return (error("socket", "couldn't create"));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if (bind(e->s, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (error("bind", "couldn't bind"));
	if (listen(e->s, 42) == -1)
		return (error("listen", "couldn't listen"));
	e->fds[e->s].type = FD_SERV;
	e->fds[e->s].fct_read = srv_accept;
	return (EXIT_SUCCESS);
}
