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
		src/client/gestion_client_list.c \
		src/client/modif_login.c \
		src/user/gestion_user_list.c \
		src/user/modif_login.c \
		src/list.c \
		src/connection.c \
		src/my_str_to_word_array.c \
		src/utils.c \
		src/handle_commands.c 	\
		src/cmd/cmd_login.c \
		src/send_infos.c \
		src/cmd/cmd_send.c 		\
		src/cmd/cmd_messages.c 	\
		src/user/modif_send.c 	\
		src/client/modif_send.c \

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
