/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:36:31 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 16:09:37 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			check_opt(char *opt)
{
	if (ft_strcmp("-ipv6", opt) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int			get_opt(t_env *e, int ac, char **av)
{
	if (ac < 2 || ac > 3)
	{
		ft_putstr_fd("Usage: ./server port", 2);
		return (EXIT_FAILURE);
	}
	if (ac == 2)
	{
		e->port = ft_atoi(av[1]);
		if (srv_create(e, e->port) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ac == 3)
	{
		if (check_opt(av[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		e->port = ft_atoi(av[2]);
		if (srv_create_ipv6(e, e->port) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
