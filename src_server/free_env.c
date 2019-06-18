/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:40:22 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:19:24 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			free_env(t_env *e)
{
	int			i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			free(e->fds[i].buff_read->tab);
			free(e->fds[i].buff_read);
			free(e->fds[i].buff_write->tab);
			free(e->fds[i].buff_write);
			free(e->fds[i].name);
		}
		i++;
	}
	free(e->fds);
	i = 0;
	while (i < e->curr_max_chan)
	{
		free(e->channels[i]);
		i++;
	}
	free(e->channels);
}
