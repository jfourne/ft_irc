/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:43:42 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 15:26:36 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void					send_name(t_env *e, int cs)
{
	int					nick_msg_len;
	char				*nick_msg;

	nick_msg_len = ft_strlen("/nick ") + ft_strlen(e->fds[cs].name);
	if ((nick_msg = (char *)malloc(sizeof(char) * (nick_msg_len + 1))) == NULL)
		return ;
	ft_strcat(nick_msg, "/nick ");
	ft_strcat(nick_msg, e->fds[cs].name);
	nick_msg[nick_msg_len] = '\n';
	send(cs, nick_msg, nick_msg_len, 0);
	free(nick_msg);
}

int						create_name(t_env *e, int cs)
{
	char				*cs_str;
	int					name_size;

	if ((cs_str = ft_itoa(cs)) == NULL)
		return (EXIT_FAILURE);
	name_size = ft_strlen(DEFAULT_NAME);
	name_size += ft_strlen(cs_str);
	name_size += 1;
	if ((e->fds[cs].name = (char *)malloc(sizeof(char) * name_size)) == NULL)
		return (EXIT_FAILURE);
	ft_bzero(e->fds[cs].name, name_size - 1);
	ft_strcat(e->fds[cs].name, DEFAULT_NAME);
	ft_strcat(e->fds[cs].name, cs_str);
	send_name(e, cs);
	free(cs_str);
	return (EXIT_SUCCESS);
}

void					print_accept(struct sockaddr_in csin, int cs)
{
	ft_putstr("New client #");
	ft_putnbr(cs);
	ft_putstr(" from ");
	ft_putstr(inet_ntoa(csin.sin_addr));
	ft_putchar(':');
	ft_putnbr(ntohs(csin.sin_port));
	ft_putchar('\n');
}

void					srv_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr *)&csin, &csin_len)) == -1)
		return ;
	clean_fd(&e->fds[cs]);
	print_accept(csin, cs);
	e->fds[cs].chan = 0;
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	if ((e->fds[cs].buff_read = (t_circle_buf *)malloc(sizeof(t_circle_buf)))
			== NULL)
		return ;
	if ((e->fds[cs].buff_write = (t_circle_buf *)malloc(sizeof(t_circle_buf)))
			== NULL)
		return ;
	if (init_buffer(e->fds[cs].buff_read) == EXIT_FAILURE
		|| init_buffer(e->fds[cs].buff_write) == EXIT_FAILURE)
		return ;
	create_name(e, cs);
}
