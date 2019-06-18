/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:55:26 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:19:20 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				find_client_name(t_env *e, char *name)
{
	int			i;

	i = 0;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT)
			&& ft_strncmp(e->fds[i].name, name,
							ft_strlen(e->fds[i].name) - 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char			*get_name(t_env *e, int cs, char *str)
{
	int			i;
	char		*name;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if ((name = (char *)malloc(sizeof(char) * i)) == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	if (str[i] != ' ')
	{
		add_buffer_str(e->fds[cs].buff_write,
		"Usage : /msg <name> <message>");
		free(name);
		return (NULL);
	}
	return (name);
}

int				find_name(t_env *e, int cs, char *str)
{
	int			i;
	char		*name;

	i = ft_strlen("/msg");
	if (!str[i] || str[i] != ' ')
	{
		add_buffer_str(e->fds[cs].buff_write,
		"Usage : /msg <name> <message>");
		return (-2);
	}
	i++;
	if ((name = get_name(e, cs, str + i)) == NULL)
		return (-2);
	i = find_client_name(e, name);
	free(name);
	return (i);
}
