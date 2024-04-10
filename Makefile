##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## make all
##

all: server client

server:
	$(MAKE) -C server/

client:
	$(MAKE) -C client/

clean:
	$(MAKE) -C server/ clean
	$(MAKE) -C client/ clean

fclean:
	$(MAKE) -C server/ fclean
	$(MAKE) -C client/ fclean

re: fclean all

.PHONY: all server client clean fclean re
