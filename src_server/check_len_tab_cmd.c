/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_len_tab_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:25:11 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:21:10 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				check_len_tab_cmd(char **tab_cmd, int len_cmd)
{
	int			i;

	i = 0;
	while (tab_cmd[i])
		i++;
	if (i == len_cmd)
	{
		if (tab_cmd[i - 1][0] == '\0' || tab_cmd[i - 1][0] == '\n')
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
