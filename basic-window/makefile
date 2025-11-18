CC = gcc
CFLAGS = -g -O0 -Wall -std=c11
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

.PHONY: all clean

all: bin/main.exe

bin/main.exe: src/main.c
	@if exist bin\main.exe del /Q bin\main.exe
	@if not exist bin mkdir bin
	$(CC) $(CFLAGS) src/main.c -o bin/main.exe $(LDFLAGS)

clean:
	@if exist bin rmdir /S /Q bin