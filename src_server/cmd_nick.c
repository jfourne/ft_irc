/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:38:11 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:22:18 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			cmd_nick(t_env *e, int cs, char **tab_cmd)
{
	char		*new_name;

	if (check_len_tab_cmd(tab_cmd, 2) == EXIT_FAILURE)
	{
		add_buffer_str(e->fds[cs].buff_write, "Usage : /nick <name>");
		return ;
	}
	if (ft_strlen(tab_cmd[1]) > 10)
	{
		add_buffer_str(e->fds[cs].buff_write,
		"Nickname too long, 9 character maximum");
		return ;
	}
	free(e->fds[cs].name);
	if ((e->fds[cs].name = ft_strdup(tab_cmd[1])) == NULL)
		return ;
	e->fds[cs].name[ft_strlen(tab_cmd[1]) - 1] = '\0';
	if ((new_name = ft_strjoin("/nick ", e->fds[cs].name)) == NULL)
		return ;
	add_buffer_str(e->fds[cs].buff_write, new_name);
	free(new_name);
}
