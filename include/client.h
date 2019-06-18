/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:11:03 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 12:28:12 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/select.h>
# include <sys/time.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/include/libft.h"

# define BUFF_SIZE 4096
# define PADDING_SPACE 100
# define FD_CLIENT_MAX 2
# define PROMPT "Client"
# define FALSE -1
# define TRUE 0
# define FD_SYSTEM 0
# define FD_SERVER 1

typedef enum		e_cmd_type
{
	EXIT,
	QUIT,
	NICK,
	MSG_SERV,
	CONNECT,
	ERROR,
	CTRL_D,
	NONE
}					t_cmd_type;

typedef struct		s_circle_buf
{
	char			*tab;
	char			*end;
	int				wcurr_len;
	char			*wbegin;
	char			*wcurr;
}					t_circle_buf;

typedef struct		s_client
{
	char			connected;
	char			name_changed;
	int				socket;
	int				max_fd;
	t_circle_buf	*buff_read;
	t_circle_buf	*buff_write;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_client;

int					g_end;

void				add_to_buffer(t_circle_buf *buffer, char buf);
void				buff_word_end(t_circle_buf *buffer);
int					check_change_name(t_client *me, char **name);
void				check_padding_space(int message_len);
int					circle_buf_cmp(char *str, t_circle_buf *buffer);
char				*circle_buf_dup(t_circle_buf *buffer);
int					client_irc(t_client *me);
int					connect_client(const char *machine, char *port_str,
						struct addrinfo hints, t_client *me);
int					connect_client_protocol(const char *machine,
						const int port, t_client *me);
int					error(char *type, char *error);
void				free_client(t_client *me);
void				free_tab(char **tab);
void				handle_signal(void);
int					init_buffer(t_circle_buf *buffer);
void				leave_server(t_client *me);
void				link_fd(t_client *me);
void				make_new_connection(t_client *me);
t_cmd_type			read_line(t_circle_buf *buffer);
int					recv_client(t_client *me, char **name);
void				reset_word(t_circle_buf *buffer);
void				send_to_server(t_client *me);
void				sig_int(int sig);
int					split_first(char *arg, t_client *me);

#endif
