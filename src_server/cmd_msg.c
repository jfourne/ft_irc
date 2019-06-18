/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:40:23 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:22:15 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				find_start_msg(char *str)
{
	int			j;
	int			space;

	j = 0;
	space = 0;
	while (str[j])
	{
		if (str[j] == ' ')
			space++;
		j++;
		if (space == 2)
			return (j);
	}
	return (j);
}

int				cmd_msg(t_env *e, int cs, char *str)
{
	int			i;
	char		*full_msg;

	if ((i = find_name(e, cs, str)) == -1)
		add_buffer_str(e->fds[cs].buff_write, "This client doesn't exist");
	else if (i >= 0)
	{
		str += find_start_msg(str);
		if ((full_msg = ft_strjoin("Message from ",
			e->fds[cs].name)) == NULL)
			return (EXIT_SUCCESS);
		if ((full_msg = ft_strjoin_and_clean(full_msg, " : ", 1)) == NULL)
			return (EXIT_SUCCESS);
		if ((full_msg = ft_strjoin_and_clean(full_msg, str, 1)) == NULL)
			return (EXIT_SUCCESS);
		full_msg[ft_strlen(full_msg) - 1] = '\0';
		add_buffer_str(e->fds[i].buff_write, full_msg);
		free(full_msg);
		client_write(e, i);
		buff_word_end(e->fds[i].buff_write);
	}
	return (EXIT_SUCCESS);
}
