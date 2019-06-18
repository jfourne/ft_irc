/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:40:40 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 16:09:25 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int					init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
		return (EXIT_FAILURE);
	e->s = 0;
	e->maxfd = rlp.rlim_cur;
	if ((e->fds = (t_fd *)malloc(sizeof(*e->fds) * e->maxfd)) == NULL)
		return (EXIT_FAILURE);
	if ((e->channels = (char **)malloc(sizeof(char *) * MAX_CHAN)) == NULL)
		return (EXIT_FAILURE);
	if ((e->channels[0] = ft_strdup("Default")) == NULL)
		return (EXIT_FAILURE);
	e->curr_max_chan = 1;
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
