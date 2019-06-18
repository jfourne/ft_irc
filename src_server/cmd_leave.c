/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_leave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:39:10 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/07 10:48:32 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			leave_chan_nb(t_env *e, int cs, int chan_nb)
{
	char		*info_str;

	if (chan_nb != e->fds[cs].chan)
		add_buffer_str(e->fds[cs].buff_write, "You're not on this channel");
	else if (chan_nb != 0)
	{
		if ((info_str = ft_strjoin("You left the channel ",
				e->channels[e->fds[cs].chan])) == NULL)
			return ;
		add_buffer_str(e->fds[cs].buff_write, info_str);
		free(info_str);
		e->fds[cs].chan = 0;
	}
}

void			leave_chan_name(t_env *e, int cs, char *chan_name)
{
	int			i;

	i = 0;
	if (chan_name[ft_strlen(chan_name) - 1] == '\n')
		chan_name[ft_strlen(chan_name) - 1] = '\0';
	while (i < e->curr_max_chan)
	{
		if (ft_strcmp(chan_name, e->channels[i]) == 0)
		{
			leave_chan_nb(e, cs, i);
			return ;
		}
		i++;
	}
	leave_chan_nb(e, cs, i);
}

void			cmd_leave(t_env *e, int cs, char **tab_cmd)
{
	if (check_len_tab_cmd(tab_cmd, 2) == EXIT_FAILURE)
	{
		add_buffer_str(e->fds[cs].buff_write,
			"Usage : /leave <channel name> or /leave <#[channel number]>");
		return ;
	}
	if (tab_cmd[1][0] == '#')
		leave_chan_nb(e, cs, ft_atoi(tab_cmd[1] + 1));
	else
		leave_chan_name(e, cs, tab_cmd[1]);
}
