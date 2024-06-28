##
## EPITECH PROJECT, 2024
## B-NWP-400-MLH-4-1-myteams-quentin.braun
## File description:
## Makefile
##

SRC	=	client.c							\
		client_initialization.c				\
		client_middleware.c					\
		../lib/my_str_to_word_array.c		\
		../lib/my_str_to_word_array_2.c		\
		../lib/manipulate_2d_array.c		\

OBJ	=	$(SRC:.c=.o)


FLAGS = -Wall -Wextra -g

NAME	=	playerWriterFight

ROOT_DIR	=	../../

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAGS)
	mv $(NAME) $(ROOT_DIR)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../../$(NAME)

re:	fclean	all
