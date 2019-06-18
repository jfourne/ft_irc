/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_irc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:26:49 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/07 10:41:19 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				init_name(char **name, char *new_name)
{
	*name = ft_strdup(new_name);
	if (*name == NULL)
		return (error("malloc", "can't allocate new memory"));
	return (EXIT_SUCCESS);
}

void			print_prompt(char *name)
{
	ft_putchar('\r');
	ft_putstr(name);
	ft_putstr(" > ");
}

int				free_name(char *name)
{
	free(name);
	return (EXIT_FAILURE);
}

void			check_cmd(t_cmd_type cmd, t_client *me)
{
	if (cmd == CONNECT)
		make_new_connection(me);
	else if (cmd == QUIT)
		leave_server(me);
	else if (cmd == MSG_SERV)
		send_to_server(me);
	if (cmd == QUIT || cmd == CONNECT || cmd == MSG_SERV || cmd == EXIT)
		buff_word_end(me->buff_read);
}

int				client_irc(t_client *me)
{
	t_cmd_type	cmd;
	char		*name;
	int			ret;

	cmd = NONE;
	if (init_name(&name, PROMPT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (cmd != EXIT && g_end == 0)
	{
		print_prompt(name);
		link_fd(me);
		ret = select(me->socket + 1, &me->fd_read, &me->fd_write, NULL, NULL);
		if (FD_ISSET(me->socket, &me->fd_read) && g_end == 0)
		{
			if (recv_client(me, &name) == EXIT_FAILURE)
				cmd = QUIT;
		}
		if (FD_ISSET(0, &me->fd_read) && g_end == 0)
			cmd = read_line(me->buff_read);
		if (cmd == ERROR)
			return (free_name(name));
		check_cmd(cmd, me);
	}
	free_name(name);
	return (EXIT_SUCCESS);
}
