NAME = ShellInvaders
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
LDFLAGS = -lncurses
SRC = $(addprefix src/, main.c  display.c )
OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME}: ${OBJ}
		${CC} ${OBJ} ${LDFLAGS} ${CFLAGS} -o ${NAME}

%.o: %.c
		${CC} -c ${<} -o ${@} ${CFLAGS}

clean:
		rm -rf ${OBJ}

fclean: clean
		rm -rf ${NAME}

re : fclean all
