##
## EPITECH PROJECT, 2024
## makefile
## File description:
## make file
##

all:
	make -C ./src/server/
	make -C ./src/client/

clean:
	rm -f ./src/server/*.o
	rm -f ./src/lib/*.o
	rm -f ./src/client/*.o
	rm -f ./src/game/*.o

fclean: clean
	rm -f ./hostWriterFight
	rm -f ./playerWriterFight

re:	fclean all
