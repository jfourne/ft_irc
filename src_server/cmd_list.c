/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:20:17 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 15:53:21 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void				cmd_list(t_env *e, int cs, char **tab_cmd)
{
	int				i;
	char			*chan_nb_name;

	if (check_len_tab_cmd(tab_cmd, 1) == EXIT_FAILURE)
	{
		add_buffer_str(e->fds[cs].buff_write, "Usage : /list");
		return ;
	}
	add_buffer_str(e->fds[cs].buff_write, "List of channels :");
	i = 0;
	while (i < e->curr_max_chan)
	{
		if ((chan_nb_name = ft_strjoin_and_clean(ft_itoa(i), " - ",
							1)) == NULL)
			return ;
		if ((chan_nb_name = ft_strjoin_and_clean(chan_nb_name, e->channels[i],
							1)) == NULL)
			return ;
		add_buffer_str(e->fds[cs].buff_write, chan_nb_name);
		free(chan_nb_name);
		i++;
	}
}
