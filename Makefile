##
## EPITECH PROJECT, 2022
## B-PSU-402-STG-4-1-strace-jeffrey.winkler
## File description:
## Makefile
##

SRC					=	src/main.c				\
						src/args.c				\
						src/execute.c			\
						src/trace.c				\
						src/print.c				\
						src/path.c				\
						src/syscalls.c

OBJ					=	$(SRC:.c=.o)

INC_DIR				=	./include

CFLAGS				=	-I$(INC_DIR) -Wall

NAME				=	my_strace

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

debug: CFLAGS += -g
debug: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
