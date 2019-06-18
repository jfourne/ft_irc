/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:25:05 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 12:24:32 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				split_first(char *arg, t_client *me)
{
	int			i;
	int			ret;
	char		**tab_arg;

	i = 0;
	if ((tab_arg = ft_strsplit(arg, ' ')) == NULL)
		return (EXIT_FAILURE);
	while (tab_arg && tab_arg[i])
		i++;
	if (i != 2)
	{
		free_tab(tab_arg);
		error("client", "usage: '[machine [port]]' or '<machine> <port>'");
		return (EXIT_FAILURE);
	}
	ret = connect_client_protocol(tab_arg[0], ft_atoi(tab_arg[1]), me);
	free_tab(tab_arg);
	return (ret);
}
