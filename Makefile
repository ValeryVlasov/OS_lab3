NAME	=	minibash

SRC		=	my_bash.c

OBJ		=	$(patsubst %.c, %.o, $(SRC))

HDR		=	my_bash.h

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror# -fsanitize=address

OPTFLAGS	=	-O2 -g

.PHONY:	all clean fclean re

all:	$(NAME)

$(NAME):	 $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:	%.c $(HDR) Makefile
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f *.o

fclean: clean
		rm -f $(NAME)

re:		fclean all

