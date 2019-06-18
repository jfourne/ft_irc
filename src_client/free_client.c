/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:28:37 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 15:56:05 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				free_client(t_client *me)
{
	free(me->buff_read->tab);
	free(me->buff_write->tab);
	free(me->buff_read);
	free(me->buff_write);
}
