UTIL=record.h record.c
MAIN=main.c
BINARY=main

all:
	gcc $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)