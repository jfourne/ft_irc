/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:38:38 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/07 10:48:37 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			join_chan_nb(t_env *e, int cs, int chan_nb, int print_error)
{
	char		*joined_chan;

	if (chan_nb < e->curr_max_chan)
	{
		e->fds[cs].chan = chan_nb;
		joined_chan = ft_strjoin("You joined channel ", e->channels[chan_nb]);
		add_buffer_str(e->fds[cs].buff_write, joined_chan);
		free(joined_chan);
	}
	else if (print_error == 1)
		add_buffer_str(e->fds[cs].buff_write, "This channel doesn't exist");
}

void			create_new_channel(t_env *e, int cs, char *chan_name)
{
	int			chan_len;

	if (e->curr_max_chan >= MAX_CHAN)
	{
		add_buffer_str(e->fds[cs].buff_write,
						"The maximum number of channel is reached");
		return ;
	}
	chan_len = ft_strlen(chan_name);
	if (chan_len > 0 && chan_name[chan_len - 1] == '\n')
		chan_name[chan_len - 1] = '\0';
	if ((e->channels[e->curr_max_chan] = ft_strdup(chan_name)) == NULL)
		return ;
	e->curr_max_chan += 1;
	add_buffer_str(e->fds[cs].buff_write, "New channel created");
	join_chan_nb(e, cs, e->curr_max_chan - 1, 0);
}

void			join_chan_name(t_env *e, int cs, char *chan_name)
{
	int			i;

	i = 0;
	if (chan_name[ft_strlen(chan_name) - 1] == '\n')
		chan_name[ft_strlen(chan_name) - 1] = '\0';
	while (i < e->curr_max_chan)
	{
		if (ft_strcmp(chan_name, e->channels[i]) == 0)
		{
			join_chan_nb(e, cs, i, 0);
			return ;
		}
		i++;
	}
	create_new_channel(e, cs, chan_name);
}

void			cmd_join(t_env *e, int cs, char **tab_cmd)
{
	if (check_len_tab_cmd(tab_cmd, 2) == EXIT_FAILURE)
	{
		add_buffer_str(e->fds[cs].buff_write,
			"Usage : /join <channel name> or /join <#[channel number]>");
		return ;
	}
	if (tab_cmd[1][0] == '#')
		join_chan_nb(e, cs, ft_atoi(tab_cmd[1] + 1), 1);
	else
		join_chan_name(e, cs, tab_cmd[1]);
}
