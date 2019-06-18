/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:37:21 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/07 10:30:17 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_cmd_type		word_created(t_circle_buf *buffer)
{
	if (circle_buf_cmp("/exit", buffer) == EXIT_SUCCESS)
		return (EXIT);
	if (circle_buf_cmp("/quit", buffer) == EXIT_SUCCESS)
		return (QUIT);
	if (circle_buf_cmp("/connect ", buffer) == EXIT_SUCCESS)
		return (CONNECT);
	return (MSG_SERV);
}

void			reset_word(t_circle_buf *buffer)
{
	buffer->wcurr = buffer->wbegin;
	buffer->wcurr_len = 0;
}

t_cmd_type		read_line(t_circle_buf *buffer)
{
	int			i;
	int			ret;
	t_cmd_type	cmd;
	char		buf[BUFF_SIZE + 1];

	if ((ret = read(0, &buf, BUFF_SIZE)) == -1)
		return (ERROR);
	if (ret == 0)
	{
		reset_word(buffer);
		ft_putchar('\n');
		return (CTRL_D);
	}
	buf[ret] = '\0';
	i = 0;
	while (i < ret)
	{
		add_to_buffer(buffer, buf[i]);
		i++;
	}
	cmd = NONE;
	if (buf[i] == '\0')
		cmd = word_created(buffer);
	return (cmd);
}
