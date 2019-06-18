/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:30:34 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:25:49 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_cmd_func		g_tab_cmd[] = {
	{"/nick", &cmd_nick},
	{"/join", &cmd_join},
	{"/leave", &cmd_leave},
	{"/list", &cmd_list},
	{"/who", &cmd_who},
};

int						parse_tab(t_env *e, int cs, char **tab_cmd)
{
	int					i;
	int					g_tab_cmd_size;

	i = 0;
	g_tab_cmd_size = sizeof(g_tab_cmd) / sizeof(t_cmd_func);
	while (i < g_tab_cmd_size)
	{
		if (ft_strncmp(tab_cmd[0], g_tab_cmd[i].cmd_name,
						ft_strlen(g_tab_cmd[i].cmd_name) - 1) == 0)
		{
			g_tab_cmd[i].f(e, cs, tab_cmd);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int						parse_line(t_env *e, int cs)
{
	int					ret;
	char				*new_str;
	char				**tab_cmd;

	if (*(e->fds[cs].buff_read->wbegin) != '/')
		return (MSG);
	if ((new_str = circle_buf_dup(e->fds[cs].buff_read)) == NULL)
		return (EXIT_FAILURE);
	if ((tab_cmd = ft_strsplit(new_str, ' ')) == NULL)
	{
		free(new_str);
		return (EXIT_FAILURE);
	}
	ret = parse_tab(e, cs, tab_cmd);
	if (ft_strncmp(new_str, "/msg", ft_strlen("/msg") - 1) == 0)
		ret = cmd_msg(e, cs, new_str);
	free(new_str);
	free_tab(tab_cmd);
	if (ret == EXIT_FAILURE)
		return (MSG);
	client_write(e, cs);
	buff_word_end(e->fds[cs].buff_write);
	return (EXIT_SUCCESS);
}
