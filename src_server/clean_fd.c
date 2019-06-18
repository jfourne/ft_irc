/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:31:37 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 15:52:08 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		free_fd(t_fd *fd)
{
	free(fd->buff_read->tab);
	free(fd->buff_read);
	free(fd->buff_write->tab);
	free(fd->buff_write);
	free(fd->name);
}

void		clean_fd(t_fd *fd)
{
	fd->chan = 0;
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
	fd->name = NULL;
}
