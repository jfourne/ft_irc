/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_change_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:43:17 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:12:35 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			name_changed(char *name)
{
	char		*name_changed;

	if ((name_changed = ft_strdup("Nickname changed to : ")) == NULL)
		return ;
	if ((name_changed = ft_strjoin_and_clean(name_changed, name, 1)) == NULL)
		return ;
	ft_putchar('\r');
	ft_putstr(name_changed);
	ft_putchar('\n');
	check_padding_space(ft_strlen(name_changed));
	free(name_changed);
}

void			change_name(char **name, char *new_name)
{
	char		*prev_name;

	prev_name = *name;
	if ((*name = ft_strdup(new_name)) == NULL)
	{
		*name = prev_name;
		return ;
	}
	free(prev_name);
}

int				check_change_name(t_client *me, char **name)
{
	char		*new_str;

	if ((new_str = circle_buf_dup(me->buff_write)) == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(new_str, "/nick ", ft_strlen("/nick ") - 1) != 0)
	{
		free(new_str);
		return (EXIT_FAILURE);
	}
	change_name(name, new_str + ft_strlen("/nick "));
	free(new_str);
	buff_word_end(me->buff_write);
	name_changed(*name);
	return (EXIT_SUCCESS);
}
