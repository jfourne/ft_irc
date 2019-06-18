/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client_protocol.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:31:07 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 12:28:31 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int						connect_client_v4(const char *machine, const int port,
										t_client *me)
{
	int					ret;
	char				*port_str;
	struct addrinfo		hints;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if ((port_str = ft_itoa(port)) == NULL)
		return (EXIT_FAILURE);
	ret = connect_client(machine, port_str, hints, me);
	free(port_str);
	return (ret);
}

int						connect_client_v6(const char *machine, const int port,
										t_client *me)
{
	int					ret;
	char				*port_str;
	struct addrinfo		hints;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	if ((port_str = ft_itoa(port)) == NULL)
		return (EXIT_FAILURE);
	ret = connect_client(machine, port_str, hints, me);
	free(port_str);
	return (ret);
}

int						connect_client_protocol(const char *machine,
									const int port, t_client *me)
{
	if (ft_strchr(machine, ':') == NULL)
		return (connect_client_v4(machine, port, me));
	else
		return (connect_client_v6(machine, port, me));
}
