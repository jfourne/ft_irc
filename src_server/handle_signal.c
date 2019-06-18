/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:48:04 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:25:12 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			sig_int(int sig)
{
	(void)sig;
	g_end = 1;
}

void			handle_signal(void)
{
	g_end = 0;
	signal(SIGINT, &sig_int);
}
