CC = gcc
CFLAGS = -g -O0 -Wall -std=c11

all: bin/main.exe

bin/main.exe: src/main.c
	mkdir -p bin
	$(CC) $(CFLAGS) src/main.c -o bin/main.exe

clean:
	rm -f bin/main.exe