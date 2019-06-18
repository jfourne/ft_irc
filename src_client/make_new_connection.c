/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_connection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:48:40 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 12:29:01 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				check_line_tab(char **line_tab)
{
	int			i;

	i = 0;
	if (!line_tab)
		return (EXIT_FAILURE);
	while (line_tab && line_tab[i])
		i++;
	if (i != 3)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			make_new_connection(t_client *me)
{
	char		*new_str;
	char		**line_tab;

	if ((new_str = circle_buf_dup(me->buff_read)) == NULL)
		return ;
	line_tab = ft_strsplit(new_str, ' ');
	free(new_str);
	if (check_line_tab(line_tab) == EXIT_FAILURE)
	{
		free_tab(line_tab);
		error("parsing", "usage '/connect <machine> [port]'");
		return ;
	}
	me->connected = FALSE;
	if (me->socket != 0)
		close(me->socket);
	connect_client_protocol(line_tab[1], ft_atoi(line_tab[2]), me);
	free_tab(line_tab);
}
