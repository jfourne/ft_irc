/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:07:29 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 12:24:39 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				init_client(t_client *me)
{
	me->connected = FALSE;
	me->name_changed = FALSE;
	me->socket = 0;
	me->max_fd = 0;
	if ((me->buff_read = (t_circle_buf *)malloc(sizeof(t_circle_buf))) == NULL)
		return (EXIT_FAILURE);
	if ((me->buff_write = (t_circle_buf *)malloc(sizeof(t_circle_buf))) == NULL)
		return (EXIT_FAILURE);
	if (init_buffer(me->buff_read) == EXIT_FAILURE
		|| init_buffer(me->buff_write) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	FD_ZERO(&me->fd_read);
	FD_ZERO(&me->fd_write);
	return (EXIT_SUCCESS);
}

int				start_client(int ac, char **av, t_client *me)
{
	int			ret;

	ac == 2 ? (ret = split_first(av[1], me))
				: (ret = connect_client_protocol(av[1], ft_atoi(av[2]), me));
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (me->connected == TRUE)
		ret = client_irc(me);
	if (me->connected == TRUE)
		close(me->socket);
	return (ret);
}

int				main(int ac, char **av)
{
	int			ret;
	t_client	me;

	if (ac < 2 || ac > 3)
	{
		return (error("client",
				"usage: '[machine [port]]' or '<machine> <port>'"));
	}
	if (init_client(&me) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	handle_signal();
	ret = start_client(ac, av, &me);
	free_client(&me);
	return (EXIT_SUCCESS);
}
