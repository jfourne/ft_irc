# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/25 10:02:40 by jfourne           #+#    #+#              #
#    Updated: 2019/06/05 10:08:25 by jfourne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT		=	client

NAME_SERVER		=	serveur

SRC_PATH_CLIENT	=	src_client

SRC_PATH_SERVER	=	src_server

SRC_NAME_CLIENT	=	add_to_buffer.c \
					check_change_name.c \
					circle_buf_cmp.c \
					circle_buf_dup.c \
					client_irc.c \
					connect_client_protocol.c \
					connect_client.c \
					error.c \
					free_client.c \
					free_tab.c \
					handle_signal.c \
					init_buffer.c \
					leave_server.c \
					link_fd.c \
					main.c \
					make_new_connection.c \
					read_line.c \
					recv_client.c \
					send_to_server.c \
					split_first.c

SRC_NAME_SERVER	=	add_buffer_str.c \
					add_to_buffer.c \
					circle_buf_dup.c \
					check_fd.c \
					check_len_tab_cmd.c \
					clean_fd.c \
					client_read.c \
					client_write.c \
					cmd_join.c \
					cmd_leave.c \
					cmd_list.c \
					cmd_msg.c \
					cmd_nick.c \
					cmd_who.c \
					do_select.c \
					error.c \
					find_name.c \
					free_env.c \
					free_tab.c \
					get_opt.c \
					handle_signal.c \
					init_buffer.c \
					init_env.c \
					init_fd.c \
					main_loop.c \
					main.c \
					parse_line.c \
					srv_accept.c \
					srv_create.c \
					srv_create_ipv6.c

OBJ_PATH_CLIENT	=	obj_client

OBJ_PATH_SERVER	=	obj_server

CIFLAGS			=	-Iinclude

LDFLAGS			=	-Llibft

LDLIBS			=	-lft

CC				=	gcc

CFLAGS			=	-Werror -Wall -Wextra

OBJ_NAME_CLIENT	=	$(SRC_NAME_CLIENT:.c=.o)

SRC_CLIENT		=	$(addprefix $(SRC_PATH_CLIENT)/,$(SRC_NAME_CLIENT))

OBJ_CLIENT		=	$(addprefix $(OBJ_PATH_CLIENT)/,$(OBJ_NAME_CLIENT))

OBJ_NAME_SERVER	=	$(SRC_NAME_SERVER:.c=.o)

SRC_SERVER		=	$(addprefix $(SRC_PATH_SERVER)/,$(SRC_NAME_SERVER))

OBJ_SERVER		=	$(addprefix $(OBJ_PATH_SERVER)/,$(OBJ_NAME_SERVER))

all:				$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):		$(OBJ_CLIENT)
					@make all -C libft
					@echo "libft created"
					@$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_CLIENT) -o $(NAME_CLIENT)
					@echo "client created"

$(OBJ_PATH_CLIENT)/%.o: $(SRC_PATH_CLIENT)/%.c
						@mkdir -p $(OBJ_PATH_CLIENT)
						@$(CC) $(CFLAGS) $(CIFLAGS) -o $@ -c $<

$(NAME_SERVER):		$(OBJ_SERVER)
					@make all -C libft
					@$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ_SERVER) -o $(NAME_SERVER)
					@echo "serveur created"

$(OBJ_PATH_SERVER)/%.o: $(SRC_PATH_SERVER)/%.c
						@mkdir -p $(OBJ_PATH_SERVER)
						@$(CC) $(CFLAGS) $(CIFLAGS) -o $@ -c $<

clean:
					@make clean -sC libft
					@rm -rf $(OBJ_CLIENT)
					@rm -rf $(OBJ_PATH_CLIENT)
					@rm -rf $(OBJ_SERVER)
					@rm -rf $(OBJ_PATH_SERVER)
					@echo "rm obj"

fclean:				clean
					@make fclean -sC libft
					@rm -rf $(NAME_CLIENT)
					@rm -rf $(NAME_SERVER)
					@echo "rm $(NAME_CLIENT)"
					@echo "rm $(NAME_SERVER)"

re:					fclean all

.PHONY:				all, clean, fclean, re
