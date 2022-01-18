CC := gcc
INCFLAGS  := -Iinclude
WARNING := -Wall
LIBFLAGS := -lncurses
SRCS=	snakeAPI.c clientAPI.c deplace.c main.c
OBJ=snakeAPI.o clientAPI.o deplace.o main.o


all: main

%.o:	%.c
	$(CC) $(WARNING) -std=c99 $(INCFLAGS) -c $< -o  $@

main: $(OBJ)
		$(CC)  $^ $(LIBFLAGS) -o $@

.PHONY:	clean

clean:
	rm -f snakeAPI.o clientAPI.o main.o deplace.o main
