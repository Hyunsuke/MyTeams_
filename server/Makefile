##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CC	= gcc

SRC	=	src/main.c 				\
		src/help.c 				\
		src/handle_args.c 		\
		src/server.c			\
		src/config.c 			\
		src/my_strcat.c 			\
		src/client/gestion_client_list.c \
		src/client/modif_login.c \
		src/client/modif_logout.c \
		src/user/gestion_user_list.c \
		src/user/modif_login.c \
		src/user/modif_logout.c \
		src/list.c \
		src/connection.c \
		src/my_str_to_word_array.c \
		src/utils.c \
		src/handle_commands.c 	\
		src/cmd/cmd_login.c \
		src/cmd/cmd_logout.c \
		src/cmd/cmd_users.c \
		src/cmd/cmd_user.c \
		src/send_info/send_data.c \
		src/send_info/send_cmd.c \
		src/cmd/cmd_send.c 		\
		src/cmd/cmd_messages.c 	\
		src/cmd/cmd_create.c \
		src/user/modif_send.c 	\
		src/client/modif_send.c \
		src/send_info/send_error.c \
		src/cmd/cmd_help.c \
		src/cmd/cmd_use.c \


OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include/ -W -Wall -Wextra -g -luuid

LDFLAGS += -L../libs/myteams
LDLIBS += -lmyteams

NAME	=	../myteams_server

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
