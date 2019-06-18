/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:16:22 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:23:56 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			check_padding_space(int message_len)
{
	while (message_len < PADDING_SPACE)
	{
		ft_putchar(' ');
		message_len++;
	}
}

void			write_circle_buf(t_circle_buf *buffer)
{
	char		*new_str;

	new_str = circle_buf_dup(buffer);
	if (new_str == NULL)
		return ;
	ft_putchar('\r');
	ft_putstr(new_str);
	check_padding_space(ft_strlen(new_str));
	ft_putchar('\n');
	free(new_str);
}

void			buff_finish(t_client *me)
{
	write_circle_buf(me->buff_write);
	buff_word_end(me->buff_write);
	reset_word(me->buff_read);
}

int				recv_client(t_client *me, char **name)
{
	int			i;
	int			ret;
	char		buf[BUFF_SIZE + 1];

	ret = recv(me->socket, buf, BUFF_SIZE, 0);
	if (ret <= 0)
	{
		ft_putstr("Server disconnected\n");
		return (EXIT_FAILURE);
	}
	if (buf[ret - 1] == '\n')
		ret--;
	buf[ret] = '\0';
	i = 0;
	while (i < ret)
	{
		add_to_buffer(me->buff_write, buf[i]);
		i++;
	}
	if (check_change_name(me, name) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (buf[i] == '\0')
		buff_finish(me);
	return (EXIT_SUCCESS);
}
