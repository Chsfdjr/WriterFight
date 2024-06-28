##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

CFLAGS = -Wall -Wextra -pthread

SRC		=		main.c 								\
				../lib/my_str_to_word_array.c		\
				../lib/my_str_to_word_array_2.c		\
				../lib/manipulate_2d_array.c		\
				../game/game.c						\
				../game/timer.c						\
				handleclient.c						\
				server.c							\

OBJ		=		$(SRC:.c=.o)

NAME		=       hostWriterFight


ROOT_DIR	=	../../

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAGS)
	mv $(NAME) $(ROOT_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: all

.PHONY: all re clean fclean
