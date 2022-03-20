NAME	=	minibash

NAME_LOOP	=	loop

NAME_KILL	=	kill

SRC		=	my_bash.c

SRC_LOOP	=	loop.c

SRC_KILL	=	kill_process.c

OBJ		=	$(patsubst %.c, %.o, $(SRC))

OBJ_LOOP		=	$(patsubst %.c, %.o, $(SRC_LOOP))

OBJ_KILL		=	$(patsubst %.c, %.o, $(SRC_KILL))

HDR		=	my_bash.h

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror# -fsanitize=address

.PHONY:	all clean fclean re

all:	$(NAME) $(NAME_KILL) $(NAME_LOOP)


$(NAME):	 $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME_KILL):	$(OBJ_KILL)
			$(CC) $(CFLAGS) $(OBJ_KILL) -o $(NAME_KILL)

$(NAME_LOOP):	$(OBJ_LOOP)
			$(CC) $(CFLAGS) $(OBJ_LOOP) -o $(NAME_LOOP)

%.o:	%.c $(HDR) Makefile
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f *.o

fclean: clean
		rm -f $(NAME) $(NAME_KILL) $(NAME_LOOP)

re:		fclean all kill loop

