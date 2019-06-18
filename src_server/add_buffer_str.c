/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_buffer_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:30:25 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 12:21:03 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			add_buffer_str(t_circle_buf *buffer, char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		add_to_buffer(buffer, str[i]);
		i++;
	}
	add_to_buffer(buffer, '\n');
}
