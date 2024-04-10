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
		src/gestion_client_list.c \
		src/list.c \
		src/connection.c \
		src/utils.c \

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include/ -W -Wall -Wextra -g -luuid

LDFLAGS += -L../libs/myteams
LDLIBS += -lmyteams

NAME	=	../myteams_server

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
