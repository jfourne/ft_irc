/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:16:53 by jfourne           #+#    #+#             */
/*   Updated: 2019/04/29 13:19:11 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int				error(char *type, char *error)
{
	ft_putstr("Error on ");
	ft_putstr(type);
	ft_putstr(": ");
	ft_putendl(error);
	return (EXIT_FAILURE);
}
