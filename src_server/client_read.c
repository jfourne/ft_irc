/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:33:30 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 15:50:34 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		create_msg_and_send(t_env *e, int cs, char *new_str)
{
	int		i;
	int		msg_len;
	char	*msg;

	i = 0;
	msg_len = ft_strlen(new_str) + ft_strlen(e->fds[cs].name) + 3;
	if ((msg = (char *)malloc(sizeof(char) * (msg_len + 1))) == NULL)
		return ;
	ft_bzero(msg, msg_len);
	ft_strcat(msg, e->fds[cs].name);
	ft_strcat(msg, " : ");
	ft_strcat(msg, new_str);
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
			&& (i != cs) && e->fds[i].chan == e->fds[cs].chan)
			send(i, msg, msg_len, 0);
		i++;
	}
	free(msg);
}

void		send_to_others(t_env *e, int cs)
{
	char	*new_str;

	if (e->fds[cs].buff_read->wcurr_len == 1
		&& *(e->fds[cs].buff_read->wbegin) == '\n')
		return ;
	if ((new_str = circle_buf_dup(e->fds[cs].buff_read)) == NULL)
		return ;
	create_msg_and_send(e, cs, new_str);
	free(new_str);
}

void		client_read_good(t_env *e, int cs, char *buf, int r)
{
	int		i;

	i = 0;
	while (i < r)
	{
		add_to_buffer(e->fds[cs].buff_read, buf[i]);
		i++;
	}
	if (i > 0)
		i--;
	if (buf[i] == '\n')
	{
		if (parse_line(e, cs) == MSG)
			send_to_others(e, cs);
		buff_word_end(e->fds[cs].buff_read);
	}
}

void		client_read(t_env *e, int cs)
{
	int		r;
	char	buf[BUFF_SIZE + 1];

	r = recv(cs, buf, BUFF_SIZE, 0);
	buf[r] = '\0';
	if (r <= 0)
	{
		ft_putstr(e->fds[cs].name);
		ft_putstr(" gone away\n");
		close(cs);
		free_fd(&e->fds[cs]);
		clean_fd(&e->fds[cs]);
	}
	else
		client_read_good(e, cs, buf, r);
}
