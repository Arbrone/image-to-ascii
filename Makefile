CC = gcc
OBJECTS = ./libs/libbmp/libbmp.c ./src/main.c
LIBS =
CFLAGS = -Wall -Wextra -O2
BINDIR = $(DESTDIR)/usr/bin
NAME = app

checkerboard: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)