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
		src/create_client.c 	\
		src/handle_message.c	\
		src/handle_commands.c	\
		src/my_str_to_word_array.c	\
		src/cmd/uuid.c	\
		src/cmd/name.c	\
		src/cmd/print.c	\
		src/cmd/print_bis.c	\
		src/cmd/print_bis_2.c	\
		src/cmd/status.c \
		src/cmd/message.c \
		src/cmd/time.c 		\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include/ -W -Wall -Wextra -g

LDFLAGS += -L../libs/myteams
LDLIBS += -lmyteams

NAME	=	../myteams_cli

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
