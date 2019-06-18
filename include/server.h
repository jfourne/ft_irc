/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:29:42 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/09 16:09:15 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/resource.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <signal.h>
# include "../libft/include/libft.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MSG		2

# define BUFF_SIZE	4096

# define MAX_CHAN	50

# define MAX(a,b)	((a > b) ? a : b)

# define DEFAULT_NAME "Client"

typedef struct		s_circle_buf
{
	char			*tab;
	char			*end;
	int				wcurr_len;
	char			*wbegin;
	char			*wcurr;
}					t_circle_buf;

typedef struct		s_fd
{
	int				chan;
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	t_circle_buf	*buff_read;
	t_circle_buf	*buff_write;
	char			*name;
}					t_fd;

typedef struct		s_env
{
	t_fd			*fds;
	int				port;
	int				maxfd;
	int				max;
	int				r;
	int				s;
	int				curr_max_chan;
	fd_set			fd_read;
	fd_set			fd_write;
	char			**channels;
}					t_env;

typedef struct		s_cmd_func
{
	char			*cmd_name;
	void			(*f)(t_env *e, int cs, char **tab_cmd);
}					t_cmd_func;

int					g_end;

void				add_buffer_str(t_circle_buf *buffer, char *str);
void				add_to_buffer(t_circle_buf *buffer, char buf);
void				buff_word_end(t_circle_buf *buffer);
char				*circle_buf_dup(t_circle_buf *buffer);
int					check_len_tab_cmd(char **tab_cmd, int len_cmd);
int					error(char *type, char *error);
void				free_env(t_env *e);
void				free_fd(t_fd *fd);
void				free_tab(char **tab);
int					find_name(t_env *e, int cs, char *str);
int					init_env(t_env *e);
int					get_opt(t_env *e, int ac, char **av);
void				handle_signal(void);
void				main_loop(t_env *e);
void				sig_int(int sig);
int					srv_create(t_env *e, int port);
int					srv_create_ipv6(t_env *e, int port);
void				srv_accept(t_env *e, int s);
void				client_read(t_env *e, int cs);
void				client_write(t_env *e, int cs);
void				clean_fd(t_fd *fd);
void				init_fd(t_env *e);
int					init_buffer(t_circle_buf *buffer);
void				do_select(t_env *e);
void				check_fd(t_env *e);
int					parse_line(t_env *e, int cs);
void				cmd_nick(t_env *e, int cs, char **tab_cmd);
void				cmd_join(t_env *e, int cs, char **tab_cmd);
void				cmd_leave(t_env *e, int cs, char **tab_cmd);
void				cmd_who(t_env *e, int cs, char **tab_cmd);
int					cmd_msg(t_env *e, int cs, char *str);
void				cmd_list(t_env *e, int cs, char **tab_cmd);

#endif
