/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:39:35 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:19:05 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			cmd_who(t_env *e, int cs, char **tab_cmd)
{
	int			i;
	char		*info_str;

	if (check_len_tab_cmd(tab_cmd, 1) == EXIT_FAILURE)
	{
		add_buffer_str(e->fds[cs].buff_write, "Usage : /who");
		return ;
	}
	if ((info_str = ft_strjoin("List of client in the channel : ",
			e->channels[e->fds[cs].chan])) == NULL)
		return ;
	add_buffer_str(e->fds[cs].buff_write, info_str);
	free(info_str);
	i = 0;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
			&& (i != cs) && e->fds[i].chan == e->fds[cs].chan)
			add_buffer_str(e->fds[cs].buff_write, e->fds[i].name);
		i++;
	}
}
