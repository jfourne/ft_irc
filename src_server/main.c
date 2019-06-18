/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:42:27 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 16:09:22 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			main(int ac, char **av)
{
	t_env	e;

	if (init_env(&e) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (get_opt(&e, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	handle_signal();
	main_loop(&e);
	if (e.s)
		close(e.s);
	free_env(&e);
	return (0);
}
