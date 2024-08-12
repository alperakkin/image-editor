# Makefile

CC = gcc
CFLAGS = -I./include


SRC = src/main.c src/argparse.c src/utils.c src/image.c src/helpers.c src/editor.c
OBJ = $(SRC:src/%.c=build/%.o)


EXTERNAL = -lpng


TARGET = bin/image-edit

all: clean build compile


build:
	mkdir -p build
	mkdir -p bin


compile: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(EXTERNAL)


build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean

clean:
	rm -rf build
	rm -rf bin