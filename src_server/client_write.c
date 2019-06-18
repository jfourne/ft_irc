/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:35:38 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:17:35 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			client_write(t_env *e, int cs)
{
	char		*new_str;

	if ((new_str = circle_buf_dup(e->fds[cs].buff_write)) == NULL)
		return ;
	send(cs, new_str, ft_strlen(new_str), 0);
	free(new_str);
}
